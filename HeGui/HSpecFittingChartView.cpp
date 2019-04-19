#include "HSpecFittingChartView_p.h"
#include "HePlugin/HCalloutChartExtend.h"
#include "HePlugin/HMarkerChartExtend.h"
#include "HePlugin/HSingleAxisChart.h"
#include "HePlugin/HPluginHelper.h"
#include <QtWidgets/QAction>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecFittingChartView::HSpecFittingChartView(QWidget *parent) :
    HZoomChartView(*new HSpecFittingChartViewPrivate, nullptr, parent)
{
    init();
}

HSpecFittingChartView::~HSpecFittingChartView()
{
    qDebug() << __func__;
}

void HSpecFittingChartView::addSeries(int id, QPolygonF value)
{
    Q_D(HSpecFittingChartView);
    if (value.size() <= 0)
        return;
    removeSeries(id);
    auto series = new QLineSeries();
    series->setName(QString("Line %1").arg(id));
    series->replace(value);
    d->chart->addSeries(series);
    d->marker->connectExtend();
    d->callout->connectExtend(series);
    d->series.insert(id, series);
}

void HSpecFittingChartView::removeSeries(int id)
{
    Q_D(HSpecFittingChartView);
    if (!d->series.contains(id))
        return;
    auto series = d->series[id];
    d->chart->removeSeries(series);
    d->callout->connectExtend(series);
    d->series.remove(id);
    delete series;
}

void HSpecFittingChartView::clearSeries()
{
    Q_D(HSpecFittingChartView);
    d->chart->removeAllSeries();
    d->marker->disconnectExtend();
    d->series.clear();
}

void HSpecFittingChartView::init()
{
    Q_D(HSpecFittingChartView);
    auto axisX = new QValueAxis;
    axisX->setLabelFormat("%d");
    axisX->setRange(0, 65535);
    axisX->setTickCount(6);
    auto axisY = new QValueAxis;
    axisY->setRange(0.8, 1);
    axisY->setTickCount(6);
    d->chart = new HSingleAxisChart;
    d->chart->setAxisX(axisX);
    d->chart->setAxisY(axisY);
    d->marker = new HMarkerChartExtend(d->chart, this);
    d->callout = new HCalloutChartExtend(d->chart, this);
    d->actionClearCallout = new QAction(tr("清除标注(&C)"));
    d->actionClearSeries = new QAction(tr("清除曲线(&C)"));
    connect(d->actionClearCallout, &QAction::triggered, d->callout, &HCalloutChartExtend::clear);
    connect(d->actionClearSeries, &QAction::triggered, this, &HSpecFittingChartView::clearSeries);
    addAction(d->actionClearCallout);
    addAction(d->actionClearSeries);
    HPluginHelper::addSeparator(this);
    setChart(d->chart);
    setWindowTitle(tr("CCD曲线"));
    HZoomChartView::init();
}

void HSpecFittingChartView::resizeEvent(QResizeEvent *e)
{
    Q_D(HSpecFittingChartView);
    if (scene())
        d->callout->updateGeometry();
    HZoomChartView::resizeEvent(e);
}

HE_GUI_END_NAMESPACE
