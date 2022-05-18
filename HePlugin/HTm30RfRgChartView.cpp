#include "HTm30RfRgChartView_p.h"
#include "HSingleAxisChart.h"
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>

HTm30RfRgChartView::HTm30RfRgChartView(QWidget *parent) :
    HZoomChartView(*new HTm30RfRgChartViewPrivate, nullptr, parent)
{
    init();
}

HTm30RfRgChartView::~HTm30RfRgChartView()
{
}

void HTm30RfRgChartView::setRfRg(double Rf, double Rg)
{
    Q_D(HTm30RfRgChartView);
    d->point->replace(0, Rf, Rg);
}

void HTm30RfRgChartView::init()
{
    Q_D(HTm30RfRgChartView);
    HZoomChartView::init();
    auto axisX = new QValueAxis;
    axisX->setLabelFormat("%d");
    axisX->setLinePenColor(Qt::black);
    axisX->setRange(50, 100);
    axisX->setTickCount(6);
    axisX->setGridLineVisible(false);
    axisX->setTitleText("<p>IES TM-30-18 R<span style='vertical-align:sub;'>f</span></p>");
    auto axisY = new QValueAxis;
    axisY->setLabelFormat("%d");
    axisY->setLinePenColor(Qt::black);
    axisY->setRange(60, 140);
    axisY->setTickCount(9);
    axisY->setGridLineVisible(false);
    axisY->setTitleText("<p>IES TM-30-18 R<span style='vertical-align:sub;'>g</span></p>");
    auto chart = new HSingleAxisChart;
    chart->setAxisX(axisX);
    chart->setAxisY(axisY);
    d->point = new QScatterSeries;
    d->point->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    d->point->setMarkerSize(10.0);
    d->point->append(80, 90);
    auto line = new QLineSeries;
    line->setPen(QPen(Qt::gray, 1, Qt::DashLine));
    line->append(0, 100);
    line->append(100, 100);

    auto color1 = QColor(220, 220, 220);
    auto color2 = QColor(170, 170, 170);
    auto line11 = new QLineSeries;
    line11->append(50.0, 60.0);
    line11->append(100.0, 100.0);
    auto line12 = new QLineSeries;
    line12->append(60.0, 60.0);
    line12->append(100.0, 100.0);
    auto line13 = new QLineSeries;
    line13->append(100.0, 60.0);
    line13->append(100.0, 100.0);
    auto line21 = new QLineSeries;
    line21->append(50.0, 140.0);
    line21->append(100.0, 100.0);
    auto line22 = new QLineSeries;
    line22->append(60.0, 140.0);
    line22->append(100.0, 100.0);
    auto line23 = new QLineSeries;
    line23->append(100.0, 140.0);
    line23->append(100.0, 100.0);
    auto area11 = new QAreaSeries;
    area11->setBrush(color1);
    area11->setBorderColor(color1);
    area11->setUpperSeries(line11);
    area11->setLowerSeries(line12);
    auto area12 = new QAreaSeries;
    area12->setBrush(color2);
    area12->setBorderColor(color2);
    area12->setUpperSeries(line12);
    area12->setLowerSeries(line13);
    auto area21 = new QAreaSeries;
    area21->setBrush(color1);
    area21->setBorderColor(color1);
    area21->setUpperSeries(line21);
    area21->setLowerSeries(line22);
    auto area22 = new QAreaSeries;
    area22->setBrush(color2);
    area22->setBorderColor(color2);
    area22->setUpperSeries(line22);
    area22->setLowerSeries(line23);
    chart->addSeries(line);
    chart->addSeries(area11);
    chart->addSeries(area12);
    chart->addSeries(area21);
    chart->addSeries(area22);
    chart->addSeries(d->point);
    chart->legend()->setVisible(false);
    setChart(chart);
    setWindowTitle(tr("Rf与Rg关系图"));
}


