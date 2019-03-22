/***************************************************************************************************
**      2018-07-03  HSingleAxisChart 单坐标系图表。
***************************************************************************************************/

#ifndef HSINGLEAXISCHART_H
#define HSINGLEAXISCHART_H

#include <QtCharts/QChart>

QT_CHARTS_USE_NAMESPACE

class HSingleAxisChartPrivate;

class HSingleAxisChart : public QChart
{
    Q_OBJECT

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

protected:
    QScopedPointer<HSingleAxisChartPrivate> d_ptr;
};

#endif // HSINGLEAXISCHART_H
