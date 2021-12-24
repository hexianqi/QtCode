#include "HTm30SpdChartView_p.h"
#include "HSingleAxisChart.h"
#include <QtCharts/QValueAxis>

HTm30SpdChartView::HTm30SpdChartView(QWidget *parent) :
    HZoomChartView(*new HTm30SpdChartViewPrivate, nullptr, parent)
{
    init();
}

HTm30SpdChartView::~HTm30SpdChartView()
{
}

void HTm30SpdChartView::setAxisXRange(double min, double max)
{
    chart()->axisX()->setRange(min, max);
}

void HTm30SpdChartView::setTest(QPolygonF value)
{
    Q_D(HTm30SpdChartView);
    d->testSeries->replace(value);
}

void HTm30SpdChartView::setReference(QPolygonF value)
{
    Q_D(HTm30SpdChartView);
    d->references->replace(value);
}

void HTm30SpdChartView::init()
{
    Q_D(HTm30SpdChartView);
    auto axisX = new QValueAxis;
    axisX->setLabelFormat("%d");
    axisX->setRange(380, 780);
    axisX->setTickCount(11);
    axisX->setTitleText("<p>Wavelength (nm)</p>");
    auto axisY = new QValueAxis;
    axisY->setLabelFormat("%d");
    axisY->setRange(0, 100);
    axisY->setTickCount(6);
    axisY->setLabelFormat("%d%");
    axisY->setTitleText("<p>Radiant power</p>");
    auto chart = new HSingleAxisChart;
    chart->setAxisX(axisX);
    chart->setAxisY(axisY);
    d->testSeries = new QLineSeries();
    d->testSeries->setName("Test");
    d->testSeries->setColor(Qt::black);
    d->references = new QLineSeries();
    d->references->setName("Reference");
    d->references->setColor(Qt::red);
    chart->addSeries(d->testSeries);
    chart->addSeries(d->references);
    setChart(chart);
    setWindowTitle(tr("相对光谱功率分布"));
    HZoomChartView::init();
}


