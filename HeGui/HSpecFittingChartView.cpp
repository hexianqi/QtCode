#include "HSpecFittingChartView_p.h"
#include "HePlugin/HCalloutChartExtend.h"
#include "HePlugin/HMarkerChartExtend.h"
#include "HePlugin/HSingleAxisChart.h"
#include "HePlugin/HPluginHelper.h"
#include <QtWidgets/QAction>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
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
    auto line = new QLineSeries();
    line->setName(QString("Line %1").arg(id));
    line->replace(value);
    auto scatter = new QScatterSeries();
    scatter->setName(QString("Scatter %1").arg(id));
    scatter->setMarkerSize(8);
    scatter->replace(value);
    d->chart->addSeries(line);
    d->chart->addSeries(scatter);
    d->marker->connectExtend();
    d->callout->connectExtend(line);
    d->lineSeries.insert(id, line);
    d->scatterSeries.insert(id, scatter);
}

void HSpecFittingChartView::removeSeries(int id)
{
    Q_D(HSpecFittingChartView);
    if (d->lineSeries.contains(id))
    {
        auto series = d->lineSeries[id];
        d->chart->removeSeries(series);
        d->callout->disconnectExtend(series);
        d->lineSeries.remove(id);
        delete series;
    }
    if (d->scatterSeries.contains(id))
    {
        auto series = d->scatterSeries[id];
        d->chart->removeSeries(series);
        d->scatterSeries.remove(id);
        delete series;
    }
}

void HSpecFittingChartView::clearSeries()
{
    Q_D(HSpecFittingChartView);
    d->chart->zoomReset();
    d->chart->removeAllSeries();
    d->marker->disconnectExtend();
    d->lineSeries.clear();
    d->scatterSeries.clear();
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
    auto clearCallout = new QAction(tr("清除标注(&C)"));
    auto clearSeries = new QAction(tr("清除曲线(&C)"));
    connect(clearCallout, &QAction::triggered, d->callout, &HCalloutChartExtend::clear);
    connect(clearSeries, &QAction::triggered, this, &HSpecFittingChartView::clearSeries);
    addAction(clearCallout);
    addAction(clearSeries);
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
