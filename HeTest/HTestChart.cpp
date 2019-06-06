#include "HTestChart.h"
#include "HePlugin/HMarkerChartExtend.h"
#include "HePlugin/HCalloutChartExtend.h"
#include "HePlugin/HVernierChartView.h"
#include <QtCore/QRandomGenerator>
#include <QtCore/QtMath>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>

QChartView *HTestChart::zoomChart()
{
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < 500; i++)
    {
        QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
        p.ry() += QRandomGenerator::global()->bounded(20);
        *series << p;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Zoom in/out example");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->createDefaultAxes();

    auto *chartView = new QChartView;
    chartView->setRubberBand(QChartView::RectangleRubberBand);
    chartView->setChart(chart);
    return chartView;
}

QChartView *HTestChart::lineChart(QList<QPolygonF> polys)
{
    auto chartView = new QChartView;
    auto chart = new QChart();
    auto marker = new HMarkerChartExtend(chart, chartView);
    if (polys.size() > 0)
    {
        auto scatter = new QScatterSeries();
        scatter->setName("Scatter");
        scatter->setMarkerSize(10);
        scatter->append(polys[0].toList());
        chart->addSeries(scatter);
    }
    for (int i = 0; i < polys.size(); i++)
    {
        auto series = new QLineSeries();
        series->setName(QString("Line %1").arg(i + 1));
        series->append(polys[i].toList());
        chart->addSeries(series);
    }
    chart->createDefaultAxes();
    chart->legend()->setAlignment(Qt::AlignRight);
    chartView->setChart(chart);
    marker->connectExtend();
    return chartView;
}

QChartView *HTestChart::diffChart(QPolygonF p1, QPolygonF p2)
{
    auto points = p1.toList();
    auto chartView = new HZoomChartView;
    auto chart = new QChart();
    auto marker = new HMarkerChartExtend(chart, chartView);
    auto callout = new HCalloutChartExtend(chart, chartView);
    auto line1 = new QLineSeries();
    auto spline1 = new QSplineSeries();
    auto scatter1 = new QScatterSeries();
    auto line2 = new QLineSeries();
    line1->setName("Line1");
    line1->append(points);
    spline1->setName("Spline1");
    spline1->append(points);
    scatter1->setName("Scatter1");
    scatter1->setMarkerSize(10);
    scatter1->append(points);
    line2->setName("Line2");
    line2->append(p2.toList());
    chart->addSeries(line1);
    chart->addSeries(spline1);
    chart->addSeries(scatter1);
    chart->addSeries(line2);
    chart->createDefaultAxes();
    chartView->setChart(chart);
    marker->connectExtend();
    callout->connectExtend();
    return chartView;
}

QChartView *HTestChart::vernierChart(QPolygonF p1, QPolygonF p2)
{
    auto points = p1.toList();
    auto chart = new QChart();
    auto line1 = new QLineSeries();
    auto spline1 = new QSplineSeries();
    auto scatter1 = new QScatterSeries();
    auto line2 = new QLineSeries();
    line1->setName("Line1");
    line1->append(points);
    spline1->setName("Spline1");
    spline1->append(points);
    scatter1->setName("Scatter1");
    scatter1->setMarkerSize(10);
    scatter1->append(points);
    line2->setName("Line2");
    line2->append(p2.toList());
    chart->addSeries(line1);
    chart->addSeries(spline1);
    chart->addSeries(scatter1);
    chart->addSeries(line2);
    chart->createDefaultAxes();
    return new HVernierChartView(chart);
}
