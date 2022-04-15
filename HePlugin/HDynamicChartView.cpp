#include "HDynamicChartView_p.h"
#include "HSingleAxisChart.h"
#include "HePlugin/HCalloutChartExtend.h"
#include "HePlugin/HMarkerChartExtend.h"
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>

HDynamicChartView::HDynamicChartView(QWidget *parent) :
    HZoomChartView(*new HDynamicChartViewPrivate, nullptr, parent)
{
    init();
}

QValueAxis *HDynamicChartView::axisX()
{
    Q_D(HDynamicChartView);
    return d->axisX;
}

QValueAxis *HDynamicChartView::axisY()
{
    Q_D(HDynamicChartView);
    return d->axisY;
}

void HDynamicChartView::clear()
{
    Q_D(HDynamicChartView);
    d->lineSeries->clear();
    d->scatterSeries->clear();
    d->axisX->setRange(0, 1);
    d->axisY->setRange(0, 1);
}

void HDynamicChartView::addPoint(QPointF point)
{
    Q_D(HDynamicChartView);
    d->lineSeries->append(point);
    d->scatterSeries->append(point);
    if (d->lineSeries->count() == 2)
    {
        auto points = d->lineSeries->points();
        d->axisX->setRange(floor(qMin(points[0].x(), points[1].x())) , ceil(qMax(points[0].x(), points[1].x())));
        d->axisY->setRange(floor(qMin(points[0].y(), points[1].y())) , ceil(qMax(points[0].y(), points[1].y())));
    }
    else if (d->lineSeries->count() > 2)
    {
        if (point.x() < d->axisX->min())
            d->axisX->setMin(floor(point.x()));
        if (point.x() > d->axisX->max())
            d->axisX->setMax(ceil(point.x()));
        if (point.y() < d->axisY->min())
            d->axisY->setMin(floor(point.y()));
        if (point.y() > d->axisY->max())
            d->axisY->setMax(ceil(point.y()));
    }
}

void HDynamicChartView::replace(QVector<QPointF> points)
{
    Q_D(HDynamicChartView);
    auto x1 = 0.0;
    auto x2 = 1.0;
    auto y1 = 0.0;
    auto y2 = 1.0;
    for (auto p : points)
    {
        if (p.x() < x1)
            x1 = p.x();
        if (p.x() > x2)
            x2 = p.x();
        if (p.y() < y1)
            y1 = p.y();
        if (p.y() > y2)
            y2 = p.y();
    }
    d->lineSeries->replace(points);
    d->scatterSeries->replace(points);
    d->axisX->setRange(10 * floor(x1 / 10) , 10 * ceil(x2 / 10));
    d->axisY->setRange(10 * floor(y1 / 10) , 10 * ceil(y2 / 10));
}

void HDynamicChartView::init()
{
    Q_D(HDynamicChartView);
    d->lineSeries = new QLineSeries();
    d->lineSeries->setName(tr("线"));
    d->scatterSeries = new QScatterSeries();
    d->scatterSeries->setName(tr("点"));
    d->scatterSeries->setMarkerSize(8);
    d->axisX = new QValueAxis;
    d->axisX->setRange(0, 1);
    d->axisX->setTickCount(6);
    d->axisY = new QValueAxis;
    d->axisY->setRange(0, 1);
    d->axisY->setTickCount(6);
    d->chart = new HSingleAxisChart;
    d->chart->setAxisX(d->axisX);
    d->chart->setAxisY(d->axisY);
    d->chart->addSeries(d->lineSeries);
    d->chart->addSeries(d->scatterSeries);
    d->marker = new HMarkerChartExtend(d->chart, this);
    d->marker->connectExtend();
    d->callout = new HCalloutChartExtend(d->chart, this);
    d->callout->connectExtend();
    setChart(d->chart);
    HZoomChartView::init();
}
