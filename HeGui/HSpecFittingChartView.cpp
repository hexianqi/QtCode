#include "HSpecFittingChartView_p.h"
#include "HePlugin/HSingleAxisChart.h"
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>

HE_GUI_BEGIN_NAMESPACE

HSpecFittingChartView::HSpecFittingChartView(QWidget *parent) :
    HZoomChartView(*new HSpecFittingChartViewPrivate, parent)
{
    init();
}

HSpecFittingChartView::~HSpecFittingChartView()
{

}

void HSpecFittingChartView::addSeries(int id, QList<QPointF> value)
{
    Q_D(HSpecFittingChartView);
    removeSeries(id);
    auto serie = new QLineSeries();
    serie->setName(QString("Line %1").arg(id));
    serie->append(value);
    d->chart->addSeries(serie);
    d->series.insert(id, serie);
}

void HSpecFittingChartView::removeSeries(int id)
{
    Q_D(HSpecFittingChartView);
    if (d->series.contains(id))
        d->series.remove(id);
}

void HSpecFittingChartView::clearSeries()
{
    Q_D(HSpecFittingChartView);
    d->chart->removeAllSeries();
    d->series.clear();
}

void HSpecFittingChartView::init()
{
    Q_D(HSpecFittingChartView);
    auto axisX = new QValueAxis;
    axisX->setRange(0, 65535);
    axisX->setTickCount(6);
    auto axisY = new QValueAxis;
    axisY->setRange(0.8, 1);
    axisY->setTickCount(6);
    d->chart = new HSingleAxisChart;
    d->chart->setAxisX(axisX);
    d->chart->setAxisY(axisY);
    setChart(d->chart);
}

HE_GUI_END_NAMESPACE
