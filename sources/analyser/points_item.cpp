#include <qstring.h>
#include <qpainter.h>
#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_interval_data.h>
#include <qwt-qt4/qwt_painter.h>
#include <qwt-qt4/qwt_scale_map.h>
#include "points_item.h"

class PointsItem::PrivateData
{
public:
    int attributes;
    QwtIntervalData data;
    QColor color;
    double reference;
};

PointsItem::PointsItem(const QwtText &title):
    QwtPlotItem(title)
{
    init();
}

PointsItem::PointsItem(const QString &title):
    QwtPlotItem(QwtText(title))
{
    init();
}

PointsItem::~PointsItem()
{
    delete d_data;
}

void PointsItem::init()
{
    d_data = new PrivateData();
    d_data->reference = 0.0;
    d_data->attributes = PointsItem::Auto;

    setItemAttribute(QwtPlotItem::AutoScale, true);
    setItemAttribute(QwtPlotItem::Legend, true);

    setZ(20.0);
}

void PointsItem::setBaseline(double reference)
{
    if ( d_data->reference != reference )
    {
        d_data->reference = reference;
        itemChanged();
    }
}

double PointsItem::baseline() const
{
    return d_data->reference;
}

void PointsItem::setData(const QwtIntervalData &data)
{
    d_data->data = data;
    itemChanged();
}

const QwtIntervalData &PointsItem::data() const
{
    return d_data->data;
}

void PointsItem::setColor(const QColor &color)
{
    if ( d_data->color != color )
    {
        d_data->color = color;
        itemChanged();
    }
}

QColor PointsItem::color() const
{
    return d_data->color;
}

QwtDoubleRect PointsItem::boundingRect() const
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


int PointsItem::rtti() const
{
    return QwtPlotItem::Rtti_PlotHistogram;
}

void PointsItem::setPointsAttribute(PointsAttribute attribute, bool on)
{
    if ( bool(d_data->attributes & attribute) == on )
        return;

    if ( on )
        d_data->attributes |= attribute;
    else
        d_data->attributes &= ~attribute;

    itemChanged();
}

bool PointsItem::testPointsAttribute(PointsAttribute attribute) const
{
    return d_data->attributes & attribute;
}

  void PointsItem::draw(QPainter * painter, const QwtScaleMap &xMap,
        const QwtScaleMap &yMap,const QRect &canvasRect) const
  {
      const QwtIntervalData &iData = d_data->data;

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

void PointsItem::drawBar(QPainter * painter,
        Qt::Orientation o, const double & x1 ,const double & x2 ,const double & y) const
{
   painter->save();

   const QColor color(painter->pen().color());


   painter->setBrush(color);
   painter->setPen(QPen(color,3,Qt::SolidLine,Qt::RoundCap));

   QwtPainter::drawPoint(painter, (x1 + x2)/2,y);


   painter->restore();
}
