#include "HAngleChartView_p.h"
#include "HePlugin/HCalloutChartExtend.h"
#include <QtCharts/QPolarChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

HE_BEGIN_NAMESPACE

HAngleChartView::HAngleChartView(QWidget *parent) :
    HPolarChartView(*new HAngleChartViewPrivate, parent)
{
    init();
}

HAngleChartView::HAngleChartView(HAngleChartViewPrivate &p, QWidget *parent) :
    HPolarChartView(p, parent)
{
}

HAngleChartView::~HAngleChartView() = default;

void HAngleChartView::setAngleFifth(double left, double right)
{
    Q_D(HAngleChartView);
    d->fifthSeries->replace(QList<QPointF>() << QPointF(left, d->maxValue) << QPointF(0, 0) << QPointF(right, d->maxValue));
}

void HAngleChartView::setAngleHalf(double left, double right)
{
    Q_D(HAngleChartView);
    d->halfSeries->replace(QList<QPointF>() << QPointF(left, d->maxValue) << QPointF(0, 0) << QPointF(right, d->maxValue));
}

void HAngleChartView::init()
{
    Q_D(HAngleChartView);
    HPolarChartView::init();
    d->originSeries = new QLineSeries;
    d->originSeries->setPen(QPen(QColor(16, 16, 16), 3));
    d->originSeries->append(-90, d->maxValue);
    d->originSeries->append(0, 0);
    d->originSeries->append(90, d->maxValue);
    d->fifthSeries = new QLineSeries;
    d->fifthSeries->setPen(QPen(Qt::green, 2));
    d->halfSeries = new QLineSeries;
    d->halfSeries->setPen(QPen(Qt::red, 2));
    d->callout = new HCalloutChartExtend(d->chart, this);
    d->callout->connectExtend();
    addSeries(d->originSeries);
    addSeries(d->fifthSeries);
    addSeries(d->halfSeries);
    addActions(d->callout->actions());
}

void HAngleChartView::resizeEvent(QResizeEvent *event)
{
    Q_D(HAngleChartView);
    if (scene())
        d->callout->updateGeometry();
    HPolarChartView::resizeEvent(event);
}

HE_END_NAMESPACE
