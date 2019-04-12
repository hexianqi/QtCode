#include "HSingleAxisChart_p.h"

HSingleAxisChart::HSingleAxisChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    HChart(*new HSingleAxisChartPrivate, parent, wFlags)
{
}

HSingleAxisChart::HSingleAxisChart(HSingleAxisChartPrivate &p, QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    HChart(p, parent, wFlags)
{
}

HSingleAxisChart::~HSingleAxisChart()
{
}

void HSingleAxisChart::addSeries(QAbstractSeries *series)
{
    Q_D(HSingleAxisChart);
    QChart::addSeries(series);
    series->attachAxis(d->axisX);
    series->attachAxis(d->axisY);
}

void HSingleAxisChart::setAxisX(QAbstractAxis *axis)
{
    Q_D(HSingleAxisChart);
    d->axisX = axis;
    QChart::setAxisX(axis);
}

void HSingleAxisChart::setAxisY(QAbstractAxis *axis)
{
    Q_D(HSingleAxisChart);
    d->axisY = axis;
    QChart::setAxisY(axis);
}

QAbstractAxis *HSingleAxisChart::axisX() const
{
    Q_D(const HSingleAxisChart);
    return d->axisX;
}

QAbstractAxis *HSingleAxisChart::axisY() const
{
    Q_D(const HSingleAxisChart);
    return d->axisY;
}
