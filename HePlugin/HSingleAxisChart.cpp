#include "HSingleAxisChart_p.h"

HSingleAxisChart::HSingleAxisChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(parent, wFlags), d_ptr(new HSingleAxisChartPrivate)
{
}

HSingleAxisChart::HSingleAxisChart(HSingleAxisChartPrivate &p, QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(parent, wFlags), d_ptr(&p)
{
}

HSingleAxisChart::~HSingleAxisChart()
{
}

void HSingleAxisChart::addSeries(QAbstractSeries *series)
{
    QChart::addSeries(series);
    series->attachAxis(d_ptr->axisX);
    series->attachAxis(d_ptr->axisY);
}

void HSingleAxisChart::setAxisX(QAbstractAxis *axis)
{
    d_ptr->axisX = axis;
    QChart::setAxisX(axis);
}

void HSingleAxisChart::setAxisY(QAbstractAxis *axis)
{
    d_ptr->axisY = axis;
    QChart::setAxisY(axis);
}

QAbstractAxis *HSingleAxisChart::axisX() const
{
    return d_ptr->axisX;
}

QAbstractAxis *HSingleAxisChart::axisY() const
{
    return d_ptr->axisY;
}
