#include "HPolarChartView_p.h"
#include <QtCharts/QPolarChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QSplineSeries>

HPolarChartView::HPolarChartView(QWidget *parent) :
    HChartView(*new HPolarChartViewPrivate, nullptr, parent)
{
    init();
}

HPolarChartView::HPolarChartView(HPolarChartViewPrivate &p, QWidget *parent) :
    HChartView(p, nullptr, parent)
{
}

HPolarChartView::~HPolarChartView() = default;

QValueAxis *HPolarChartView::axisAngular()
{
    Q_D(HPolarChartView);
    return d->axisAngular;
}

QValueAxis *HPolarChartView::axisRadial()
{
    Q_D(HPolarChartView);
    return d->axisRadial;
}

void HPolarChartView::clear()
{
    Q_D(HPolarChartView);
    d->series->clear();
    d->axisRadial->setRange(0, 1);
}

void HPolarChartView::replace(QVector<QPointF> points)
{
    Q_D(HPolarChartView);
    auto r1 = 0.0;
    auto r2 = 1.0;
    for (auto p : points)
    {
        if (p.y() < r1)
            r1 = p.y();
        if (p.y() > r2)
            r2 = p.y();
    }
    d->series->replace(points);
    d->axisRadial->setRange(10 * floor(r1 / 10) , 10 * ceil(r2 / 10));
}

void HPolarChartView::init()
{
    Q_D(HPolarChartView);
    d->axisAngular = new QValueAxis();
    d->axisAngular->setRange(-180, 180);
    d->axisAngular->setTickCount(9);
    d->axisAngular->setLabelFormat("%d");
//    d->axisAngular->setShadesVisible(true);
//    d->axisAngular->setShadesBrush(QColor(249, 249, 255));
    d->axisRadial = new QValueAxis();
    d->axisRadial->setTickCount(6);
    d->axisRadial->setRange(0, 1);
    d->axisRadial->setLabelFormat("%.1f");
    d->series = new QSplineSeries();
    d->chart = new QPolarChart;
    d->chart->addAxis(d->axisAngular, QPolarChart::PolarOrientationAngular);
    d->chart->addAxis(d->axisRadial, QPolarChart::PolarOrientationRadial);
    d->chart->addSeries(d->series);
    d->series->attachAxis(d->axisRadial);
    d->series->attachAxis(d->axisAngular);
    d->chart->legend()->setVisible(false);
    setChart(d->chart);
    HChartView::init();
}
