#include "HCIE1931View_p.h"
#include "HCIE1931Chart.h"
#include "HPositionTracking.h"
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

void HCIE1931View::resizeEvent(QResizeEvent *e)
{
    if (scene())
    {
        auto size = e->size();
        scene()->setSceneRect(QRect(QPoint(0, 0), size));
        chart()->resize(size);
    }
    HZoomChartView::resizeEvent(e);
}

void HCIE1931View::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HCIE1931View);
    d->tracking->mouseMoveEvent(e);
    HZoomChartView::mouseMoveEvent(e);
}

void HCIE1931View::updatePosition(QPointF pos)
{
    Q_D(HCIE1931View);
    auto p = chart()->mapToValue(pos);
    d->tracking->setText(QString("(%1, %2)").arg(p.x()).arg(p.y()));
}

void HCIE1931View::init()
{
    Q_D(HCIE1931View);
    d->chart = new HCIE1931Chart;
    d->tracking = new HPositionTracking(this);
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
    d->actionSeparators << HPluginHelper::addSeparator(this);
    addAction(d->actionEnableCIE);
    addAction(d->actionEnableHorseshoe);
    addAction(d->actionEnablePlanckian);
    addAction(d->actionEnableGrade);
    d->actionSeparators << HPluginHelper::addSeparator(this);
    addAction(d->actionEnablePoint);
    addAction(d->actionClearPoint);
    connect(d->tracking, &HPositionTracking::positionChanged, this, updatePosition);
    connect(d->chart, &QChart::plotAreaChanged, d->tracking, &HPositionTracking::setValidRegion);
    connect(d->actionEnableCIE, &QAction::toggled, d->chart, &HCIE1931Chart::setEnableCIE);
    connect(d->actionEnableHorseshoe, &QAction::toggled, d->chart, &HCIE1931Chart::setEnableHorseshoe);
    connect(d->actionEnablePlanckian, &QAction::toggled, d->chart, &HCIE1931Chart::setEnablePlanckian);
    connect(d->actionEnableGrade, &QAction::toggled, d->chart, &HCIE1931Chart::setEnableGrade);
    connect(d->actionEnablePoint, &QAction::toggled, d->chart, &HCIE1931Chart::setEnablePoint);
    connect(d->actionClearPoint, &QAction::toggled, d->chart, &HCIE1931Chart::clearPoint);
    setChart(d->chart);
}
