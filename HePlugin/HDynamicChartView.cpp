#include "HDynamicChartView_p.h"
#include "HSingleAxisChart.h"
#include "HePlugin/HCalloutChartExtend.h"
#include "HePlugin/HMarkerChartExtend.h"
#include "HePlugin/HPluginHelper.h"
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

QLineSeries *HDynamicChartView::lineSeries()
{
    Q_D(HDynamicChartView);
    return d->lineSeries;
}

QScatterSeries *HDynamicChartView::scatterSeries()
{
    Q_D(HDynamicChartView);
    return d->scatterSeries;
}

void HDynamicChartView::clear()
{
    Q_D(HDynamicChartView);
    d->lineSeries->clear();
    d->scatterSeries->clear();
    d->axisX->setRange(0, 1);
    d->axisY->setRange(0, 1);
}

void HDynamicChartView::addPoint(double x, double y)
{
    addPoint(QPointF(x, y));
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

void HDynamicChartView::replace(QVector<QPointF> points, bool rescale, int baseX, int baseY)
{
    Q_D(HDynamicChartView);
    if (rescale && !points.isEmpty())
    {
        auto x0 = pow(10.0, baseX);
        auto x1 = points.first().x() - x0 * 0.05;
        auto x2 = points.first().x() + x0 * 0.05;
        auto y0 = pow(10.0, baseY);
        auto y1 = points.first().y() - y0 * 0.05;
        auto y2 = points.first().y() + y0 * 0.05;
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

        d->axisX->setRange(x0 * floor(x1 / x0) , x0 * ceil(x2 / x0));
        d->axisY->setRange(y0 * floor(y1 / y0) , y0 * ceil(y2 / y0));
    }
    d->lineSeries->replace(points);
    d->scatterSeries->replace(points);
}

void HDynamicChartView::init()
{
    Q_D(HDynamicChartView);
    HZoomChartView::init();
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
    HPluginHelper::addSeparator(this);
    addActions(d->callout->actions());
    setChart(d->chart);
}

void HDynamicChartView::resizeEvent(QResizeEvent *event)
{
    Q_D(HDynamicChartView);
    if (scene())
        d->callout->updateGeometry();
    HZoomChartView::resizeEvent(event);
}
