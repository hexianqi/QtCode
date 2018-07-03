#include "HCIE1931View_p.h"
#include "HCIE1931Chart.h"
#include "HPositionTracking.h"
#include "HPositionTrackingGraphics.h"
#include "HPluginHelper.h"
#include <QAction>

HCIE1931ViewPrivate::HCIE1931ViewPrivate(HCIE1931View *q)
    : HZoomChartViewPrivate(q)
{
}

HCIE1931View::HCIE1931View(QWidget *parent)
    : HZoomChartView(*new HCIE1931ViewPrivate(this), parent)
{
    init();
}

HCIE1931View::~HCIE1931View()
{
}

HCIE1931Chart *HCIE1931View::cieChart()
{
    Q_D(HCIE1931View);
    return d->chart;
}

HPositionTracking *HCIE1931View::tracking()
{
    Q_D(HCIE1931View);
    return d->tracking;
}

void HCIE1931View::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HCIE1931View);
    d->tracking->mouseMoveEvent(e);
    HZoomChartView::mouseMoveEvent(e);
}

void HCIE1931View::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_D(HCIE1931View);
    if (d->tracking->isEnable())
        emit mouseDoubleClicked(chart()->mapToValue(e->pos()));
    HZoomChartView::mouseMoveEvent(e);
}

void HCIE1931View::handlePlotAreaChanged(QRectF value)
{
    Q_D(HCIE1931View);
    d->tracking->setValidRegion(value);
    d->pointFocus->setPos(value.right() - d->pointFocus->boundingRect().width() - 10, value.top() + 10);
}

void HCIE1931View::handlePointFocusChanged(QPointF pos)
{
    Q_D(HCIE1931View);
    d->pointFocus->setText(QString("(%1, %2)").arg(pos.x(), 0, 'f', 4).arg(pos.y(), 0, 'f', 4));
}

void HCIE1931View::handlePositionChanged(QPointF pos)
{
    Q_D(HCIE1931View);
    auto p = chart()->mapToValue(pos);
    d->tracking->setText(QString("(%1, %2)").arg(p.x(), 0, 'f', 4).arg(p.y(), 0, 'f', 4));
}

void HCIE1931View::init()
{
    Q_D(HCIE1931View);
    d->chart = new HCIE1931Chart;
    d->tracking = new HPositionTracking(this);
    d->tracking->setControl(new HPositionTrackingGraphics(d->chart));
    d->pointFocus = new QGraphicsSimpleTextItem(d->chart);
    d->pointFocus->setPen(QPen(Qt::red));
    d->pointFocus->setZValue(100);
    d->pointFocus->setText(QString("(%1, %2)").arg(0.0, 0, 'f', 4).arg(0.0, 0, 'f', 4));
    d->actionEnableCIE = new QAction(tr("色品图(&E)"));
    d->actionEnableCIE->setCheckable(true);
    d->actionEnableCIE->setChecked(d->chart->isEnableCIE());
    d->actionEnableHorseshoe = new QAction(tr("马蹄线(&H)"));
    d->actionEnableHorseshoe->setCheckable(true);
    d->actionEnableHorseshoe->setChecked(d->chart->isEnableHorseshoe());
    d->actionEnablePlanckian = new QAction(tr("黑体轨迹(&P)"));
    d->actionEnablePlanckian->setCheckable(true);
    d->actionEnablePlanckian->setChecked(d->chart->isEnablePlanckian());
    d->actionEnableGrade = new QAction(tr("分级区域(&S)"));
    d->actionEnableGrade->setCheckable(true);
    d->actionEnableGrade->setChecked(d->chart->isEnableGrade());
    d->actionEnablePoint = new QAction(tr("打点记录(&O)"));
    d->actionEnablePoint->setCheckable(true);
    d->actionEnablePoint->setChecked(d->chart->isEnablePoint());
    d->actionClearPoint = new QAction(tr("清除打点记录(&C)"));
    HPluginHelper::addSeparator(this);
    addAction(d->actionEnableCIE);
    addAction(d->actionEnableHorseshoe);
    addAction(d->actionEnablePlanckian);
    addAction(d->actionEnableGrade);
    HPluginHelper::addSeparator(this);
    addAction(d->actionEnablePoint);
    addAction(d->actionClearPoint);
    connect(d->chart, &QChart::plotAreaChanged, this, handlePlotAreaChanged);
    connect(d->chart, &HCIE1931Chart::pointFocusChanged, this, handlePointFocusChanged);
    connect(d->tracking, &HPositionTracking::positionChanged, this, handlePositionChanged);
    connect(d->actionEnableCIE, &QAction::toggled, d->chart, &HCIE1931Chart::setEnableCIE);
    connect(d->actionEnableHorseshoe, &QAction::toggled, d->chart, &HCIE1931Chart::setEnableHorseshoe);
    connect(d->actionEnablePlanckian, &QAction::toggled, d->chart, &HCIE1931Chart::setEnablePlanckian);
    connect(d->actionEnableGrade, &QAction::toggled, d->chart, &HCIE1931Chart::setEnableGrade);
    connect(d->actionEnablePoint, &QAction::toggled, d->chart, &HCIE1931Chart::setEnablePoint);
    connect(d->actionClearPoint, &QAction::triggered, d->chart, &HCIE1931Chart::clearPoint);
    setChart(d->chart);
}
