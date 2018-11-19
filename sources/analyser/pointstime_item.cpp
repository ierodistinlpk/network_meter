#include <qstring.h>
#include <qpainter.h>
#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_data.h>
#include <qwt-qt4/qwt_painter.h>
#include <qwt-qt4/qwt_scale_map.h>
#include "pointstime_item.h"

class PointsTimeItem::PrivateData
{
public:
    int attributes;
    QwtArrayData data;
    QColor color;
    double reference;
};

PointsTimeItem::PointsTimeItem(const QwtText &title):
    QwtPlotItem(title)
{
    init();
}

PointsTimeItem::PointsTimeItem(const QString &title):
    QwtPlotItem(QwtText(title))
{
    init();
}

PointsTimeItem::~PointsTimeItem()
{
    delete d_data;
}

void PointsTimeItem::init()
{
    d_data = new PrivateData();
    d_data->reference = 0.0;
    d_data->attributes = PointsTimeItem::Auto;

    setItemAttribute(QwtPlotItem::AutoScale, true);
    setItemAttribute(QwtPlotItem::Legend, true);

    setZ(20.0);
}

void PointsTimeItem::setBaseline(double reference)
{
    if ( d_data->reference != reference )
    {
        d_data->reference = reference;
        itemChanged();
    }
}

double PointsTimeItem::baseline() const
{
    return d_data->reference;
}

void PointsTimeItem::setData(const QwtArrayData &data)
{
    d_data->data = data;
    itemChanged();
}

const QwtArrayData &PointsTimeItem::data() const
{
    return d_data->data;
}

void PointsTimeItem::setColor(const QColor &color)
{
    if ( d_data->color != color )
    {
        d_data->color = color;
        itemChanged();
    }
}

QColor PointsTimeItem::color() const
{
    return d_data->color;
}

QwtDoubleRect PointsTimeItem::boundingRect() const
{
    QwtDoubleRect rect = d_data->data.boundingRect();
    if ( !rect.isValid() ) 
        return rect;

    if ( d_data->attributes & Xfy ) 
    {
        rect = QwtDoubleRect( rect.y(), rect.x(), 
            rect.height(), rect.width() );

        if ( rect.left() > d_data->reference ) 
            rect.setLeft( d_data->reference );
        else if ( rect.right() < d_data->reference ) 
            rect.setRight( d_data->reference );
    } 
    else 
    {
        if ( rect.bottom() < d_data->reference ) 
            rect.setBottom( d_data->reference );
        else if ( rect.top() > d_data->reference ) 
            rect.setTop( d_data->reference );
    }

    return rect;
}


int PointsTimeItem::rtti() const
{
    return QwtPlotItem::Rtti_PlotHistogram;
}

void PointsTimeItem::setPointsAttribute(PointsAttribute attribute, bool on)
{
    if ( bool(d_data->attributes & attribute) == on )
        return;

    if ( on )
        d_data->attributes |= attribute;
    else
        d_data->attributes &= ~attribute;

    itemChanged();
}

bool PointsTimeItem::testPointsAttribute(PointsAttribute attribute) const
{
    return d_data->attributes & attribute;
}

  void PointsTimeItem::draw(QPainter * painter, const QwtScaleMap &xMap,
        const QwtScaleMap &yMap,const QRect &canvasRect) const
  {
      const QwtArrayData &iData = d_data->data;

    painter->setPen(QPen(d_data->color));

    for ( int i = 0; i < (int)iData.size(); i++ )
    {

            int x1 = xMap.transform(iData.interval(i).minValue());
            int x2 = xMap.transform(iData.interval(i).maxValue());

            if ( x1 > x2 )
                qSwap(x1, x2);
            double y =  yMap.transform(iData.value(i));
            drawBar(painter, Qt::Vertical,x1,x2, y );
    }
}

void PointsTimeItem::drawBar(QPainter * painter,
        Qt::Orientation o, const double & x1 ,const double & x2 ,const double & y) const
{
   painter->save();

   const QColor color(painter->pen().color());


   painter->setBrush(color);
   painter->setPen(QPen(color,4,Qt::SolidLine,Qt::RoundCap));

   QwtPainter::drawPoint(painter, (x1 + x2)/2,y);


   painter->restore();
}
