#include "HCie1931ChartView_p.h"
#include "HCie1931Chart.h"
#include "HPositionTracking.h"
#include "HPluginHelper.h"
#include <QtWidgets/QAction>

HCie1931ChartView::HCie1931ChartView(QWidget *parent) :
    HZoomChartView(*new HCie1931ChartViewPrivate, nullptr, parent)
{
    init();
}

void HCie1931ChartView::setEnableTracking(bool b)
{
    Q_D(HCie1931ChartView);
    d->tracking->setEnable(b);
    d->positionItem->setVisible(b);
}

HCie1931Chart *HCie1931ChartView::chart()
{
    Q_D(HCie1931ChartView);
    return d->chart;
}

void HCie1931ChartView::init()
{
    Q_D(HCie1931ChartView);
    HZoomChartView::init();
    d->chart = new HCie1931Chart;
    d->tracking = new HPositionTracking(this);
    d->positionItem = new QGraphicsSimpleTextItem(d->chart);
    d->positionItem->setZValue(100);
    d->pointFocusItem = new QGraphicsSimpleTextItem(d->chart);
    d->pointFocusItem->setPen(QPen(Qt::red));
    d->pointFocusItem->setZValue(100);
    d->pointFocusItem->setText(QString("(%1, %2)").arg(0.0, 0, 'f', 4).arg(0.0, 0, 'f', 4));
    auto enableCIE = new QAction(tr("色品图(&E)"));
    enableCIE->setCheckable(true);
    enableCIE->setChecked(d->chart->isEnableCIE());
    auto enableHorseshoe = new QAction(tr("马蹄线(&H)"));
    enableHorseshoe->setCheckable(true);
    enableHorseshoe->setChecked(d->chart->isEnableHorseshoe());
    auto enablePlanckian = new QAction(tr("黑体轨迹(&P)"));
    enablePlanckian->setCheckable(true);
    enablePlanckian->setChecked(d->chart->isEnablePlanckian());
    auto enableGrade = new QAction(tr("分级区域(&S)"));
    enableGrade->setCheckable(true);
    enableGrade->setChecked(d->chart->isEnableGrade());
    auto enablePoint = new QAction(tr("打点记录(&O)"));
    enablePoint->setCheckable(true);
    enablePoint->setChecked(d->chart->isEnablePoint());
    auto clearPoint = new QAction(tr("清除打点记录(&C)"));
    HPluginHelper::addSeparator(this);
    addAction(enableCIE);
    addAction(enableHorseshoe);
    addAction(enablePlanckian);
    addAction(enableGrade);
    HPluginHelper::addSeparator(this);
    addAction(enablePoint);
    addAction(clearPoint);
    connect(d->chart, &HCie1931Chart::plotAreaChanged, this, &HCie1931ChartView::handlePlotAreaChanged);
    connect(d->chart, &HCie1931Chart::pointFocusChanged, this, &HCie1931ChartView::handlePointFocusChanged);
    connect(d->tracking, &HPositionTracking::positionChanged, this, &HCie1931ChartView::handlePositionChanged);
    connect(enableCIE, &QAction::toggled, d->chart, &HCie1931Chart::setEnableCIE);
    connect(enableHorseshoe, &QAction::toggled, d->chart, &HCie1931Chart::setEnableHorseshoe);
    connect(enablePlanckian, &QAction::toggled, d->chart, &HCie1931Chart::setEnablePlanckian);
    connect(enableGrade, &QAction::toggled, d->chart, &HCie1931Chart::setEnableGrade);
    connect(enablePoint, &QAction::toggled, d->chart, &HCie1931Chart::setEnablePoint);
    connect(clearPoint, &QAction::triggered, d->chart, &HCie1931Chart::clearPoint);
    setChart(d->chart);
    setWindowTitle(tr("色品图-CIE1931"));
}

void HCie1931ChartView::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(HCie1931ChartView);
    d->tracking->mouseMoveEvent(event);
    HZoomChartView::mouseMoveEvent(event);
}

void HCie1931ChartView::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_D(HCie1931ChartView);
    if (d->tracking->isEnable())
        emit mouseDoubleClicked(chart()->mapToValue(event->pos()));
    HZoomChartView::mouseMoveEvent(event);
}

void HCie1931ChartView::handlePlotAreaChanged(QRectF value)
{
    Q_D(HCie1931ChartView);
    d->tracking->setValidRegion(value);
    d->positionItem->setPos(value.left() + 5, value.top() + 5);
    d->pointFocusItem->setPos(value.right() - d->pointFocusItem->boundingRect().width() - 5, value.top() + 5);
}

void HCie1931ChartView::handlePointFocusChanged(QPointF pos)
{
    Q_D(HCie1931ChartView);
    d->pointFocusItem->setText(QString("(%1, %2)").arg(pos.x(), 0, 'f', 4).arg(pos.y(), 0, 'f', 4));
}

void HCie1931ChartView::handlePositionChanged(QPointF pos)
{
    Q_D(HCie1931ChartView);
    auto p = chart()->mapToValue(pos);
    d->positionItem->setText(QString("(%1, %2)").arg(p.x(), 0, 'f', 4).arg(p.y(), 0, 'f', 4));
}
