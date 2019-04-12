/***************************************************************************************************
**      2018-07-03  HSingleAxisChart 单坐标系图表。
***************************************************************************************************/

#ifndef HSINGLEAXISCHART_H
#define HSINGLEAXISCHART_H

#include "HChart.h"

class HSingleAxisChartPrivate;

class QDESIGNER_WIDGET_EXPORT HSingleAxisChart : public HChart
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSingleAxisChart)

public:
    explicit HSingleAxisChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
    ~HSingleAxisChart();

public:
    void addSeries(QAbstractSeries *);
    void setAxisX(QAbstractAxis *);
    void setAxisY(QAbstractAxis *);
    QAbstractAxis *axisX() const;
    QAbstractAxis *axisY() const;

protected:
    HSingleAxisChart(HSingleAxisChartPrivate &p, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
};

#endif // HSINGLEAXISCHART_H
