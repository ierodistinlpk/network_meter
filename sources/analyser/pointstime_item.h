/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifndef POINTSTIME_ITEM_H
#define POINTSTIME_ITEM_H

#include <qglobal.h>
#include <qcolor.h>

#include <qwt-qt4/qwt_plot_item.h>
#include <qwt-qt4/qwt_data.h>
class QwtArrayData;
class QString;

class PointsTimeItem: public QwtPlotItem
{
public:
    explicit PointsTimeItem(const QString &title = QString::null);
    explicit PointsTimeItem(const QwtText &title);
    virtual ~PointsTimeItem();

    void setData(const QwtArrayData &data);
    const QwtArrayData &data() const;

    void setColor(const QColor &);
    QColor color() const;

    QwtDoubleRect boundingRect() const;

    int rtti() const;

    void draw(QPainter *, const QwtScaleMap &xMap,
        const QwtScaleMap &yMap, const QRect &canvasRect) const;

    void setBaseline(double reference);
    double baseline() const;

    enum PointsAttribute
    {
        Auto = 0,
        Xfy = 1
    };

    void setPointsAttribute(PointsAttribute, bool on = true);
    bool testPointsAttribute(PointsAttribute) const;

protected:
    void drawBar(QPainter *,
        Qt::Orientation o, const double & x1 ,const double & x2 ,const double & y) const;

private:
    void init();

    class PrivateData;
    PrivateData *d_data;
};

#endif
