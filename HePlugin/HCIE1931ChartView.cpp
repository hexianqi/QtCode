#include "HCIE1931ChartView_p.h"
#include "HCIE1931Chart.h"
#include "HPositionTracking.h"
#include "HPluginHelper.h"
#include <QtWidgets/QAction>

HCIE1931ChartView::HCIE1931ChartView(QWidget *parent) :
    HZoomChartView(*new HCIE1931ChartViewPrivate, nullptr, parent)
{
    init();
}

HCIE1931ChartView::~HCIE1931ChartView()
{
}

void HCIE1931ChartView::setEnableTracking(bool b)
{
    Q_D(HCIE1931ChartView);
    d->tracking->setEnable(b);
    d->positionItem->setVisible(b);
}

HCIE1931Chart *HCIE1931ChartView::chart()
{
    Q_D(HCIE1931ChartView);
    return d->chart;
}

void HCIE1931ChartView::init()
{
    Q_D(HCIE1931ChartView);
    d->chart = new HCIE1931Chart;
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
    connect(d->chart, &HCIE1931Chart::plotAreaChanged, this, &HCIE1931ChartView::handlePlotAreaChanged);
    connect(d->chart, &HCIE1931Chart::pointFocusChanged, this, &HCIE1931ChartView::handlePointFocusChanged);
    connect(d->tracking, &HPositionTracking::positionChanged, this, &HCIE1931ChartView::handlePositionChanged);
    connect(enableCIE, &QAction::toggled, d->chart, &HCIE1931Chart::setEnableCIE);
    connect(enableHorseshoe, &QAction::toggled, d->chart, &HCIE1931Chart::setEnableHorseshoe);
    connect(enablePlanckian, &QAction::toggled, d->chart, &HCIE1931Chart::setEnablePlanckian);
    connect(enableGrade, &QAction::toggled, d->chart, &HCIE1931Chart::setEnableGrade);
    connect(enablePoint, &QAction::toggled, d->chart, &HCIE1931Chart::setEnablePoint);
    connect(clearPoint, &QAction::triggered, d->chart, &HCIE1931Chart::clearPoint);
    setChart(d->chart);
    HZoomChartView::init();
}

void HCIE1931ChartView::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HCIE1931ChartView);
    d->tracking->mouseMoveEvent(e);
    HZoomChartView::mouseMoveEvent(e);
}

void HCIE1931ChartView::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_D(HCIE1931ChartView);
    if (d->tracking->isEnable())
        emit mouseDoubleClicked(chart()->mapToValue(e->pos()));
    HZoomChartView::mouseMoveEvent(e);
}

void HCIE1931ChartView::handlePlotAreaChanged(QRectF value)
{
    Q_D(HCIE1931ChartView);
    d->tracking->setValidRegion(value);
    d->positionItem->setPos(value.left() + 5, value.top() + 5);
    d->pointFocusItem->setPos(value.right() - d->pointFocusItem->boundingRect().width() - 5, value.top() + 5);
}

void HCIE1931ChartView::handlePointFocusChanged(QPointF pos)
{
    Q_D(HCIE1931ChartView);
    d->pointFocusItem->setText(QString("(%1, %2)").arg(pos.x(), 0, 'f', 4).arg(pos.y(), 0, 'f', 4));
}

void HCIE1931ChartView::handlePositionChanged(QPointF pos)
{
    Q_D(HCIE1931ChartView);
    auto p = chart()->mapToValue(pos);
    d->positionItem->setText(QString("(%1, %2)").arg(p.x(), 0, 'f', 4).arg(p.y(), 0, 'f', 4));
}
