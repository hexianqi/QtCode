/***************************************************************************************************
**      2021-12-02  HTm30BarChart
***************************************************************************************************/

#pragma once

#include "HSingleAxisChart.h"

QT_CHARTS_BEGIN_NAMESPACE
class QBarSeries;
class QBarSet;
QT_CHARTS_END_NAMESPACE

class HTm30BarChartPrivate;

class QDESIGNER_WIDGET_EXPORT HTm30BarChart : public HSingleAxisChart
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTm30BarChart)

public:
    explicit HTm30BarChart(int count, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
    ~HTm30BarChart() override;

public:
    QBarSeries *series();

public:
    void setBarValue(QList<double>);
    void setBarColor(QList<QColor>);

protected:
    HTm30BarChart(HTm30BarChartPrivate &p, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());

protected:
    virtual void initBar(int count);
    virtual QColor color(int i);
};



