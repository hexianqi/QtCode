#include "HChromatismChartView_p.h"
#include "HChromatismChart.h"
#include "HeAlgorithm/HMath.h"

HE_ALGORITHM_USE_NAMESPACE

HChromatismChartView::HChromatismChartView(QWidget *parent) :
    HZoomChartView(*new HChromatismChartViewPrivate, nullptr, parent)
{
    init();
}

HChromatismChartView::HChromatismChartView(HChromatismChartViewPrivate &p, QWidget *parent) :
    HZoomChartView(p, nullptr, parent)
{
}

void HChromatismChartView::handlePlotAreaChanged(QRectF value)
{
    Q_D(HChromatismChartView);
    d->pointFocusItem->setPos(value.right() - d->pointFocusItem->boundingRect().width() - 5, value.top() + 5);
}

void HChromatismChartView::setData(const QVariantMap &value)
{
    Q_D(HChromatismChartView);
    if (value.contains("[标题]"))
        d->chart->setTitle(value.value("[标题]").toString());
    if (value.contains("[标准Sdcm]"))
        d->sdcmStd = value.value("[标准Sdcm]").toDouble();
    if (value.contains("[中心点]"))
        d->pointCenter = value.value("[中心点]").toPointF();
    if (value.contains("[旋转角]"))
        d->theta = value.value("[旋转角]").toDouble();
    if (value.contains("[轴A]"))
        d->axisA = value.value("[轴A]").toDouble();
    if (value.contains("[轴B]"))
        d->axisB = value.value("[轴B]").toDouble();
    if (value.contains("[测试点]"))
        d->pointFocus = value.value("[测试点]").toPointF();
    if (value.contains("[测试Sdcm]"))
        d->sdcmFocus = value.value("[测试Sdcm]").toDouble();

    d->chart->setEllipse(HMath::calcEllipse(d->pointCenter, d->sdcmStd, d->theta, d->axisA, d->axisB));
    d->chart->setPointCenter(d->pointCenter);
    d->chart->setPointFocus(d->pointFocus);
    d->chart->createFixAxes();
    d->chart->setAxesXTitle(tr("标准 %1SDCM - 目标值x=%2,y=%3").arg(d->sdcmStd, 0, 'f', 1).arg(d->pointCenter.x(), 0, 'f', 3).arg(d->pointCenter.y(), 0, 'f', 3));
    d->pointFocusItem->setText(tr("(%2, %3)\n      %1SDCM").arg(d->sdcmFocus, 0, 'f', 1).arg(d->pointFocus.x(), 0, 'f', 4).arg(d->pointFocus.y(), 0, 'f', 4));
}

void HChromatismChartView::init()
{
    Q_D(HChromatismChartView);
    d->chart = new HChromatismChart;
    d->pointFocusItem = new QGraphicsSimpleTextItem(d->chart);
    d->pointFocusItem->setPen(QPen(Qt::red));
    d->pointFocusItem->setZValue(100);
    d->pointFocusItem->setText(tr("(%2, %3)\n      %1SDCM").arg(d->sdcmFocus, 0, 'f', 1).arg(d->pointFocus.x(), 0, 'f', 4).arg(d->pointFocus.y(), 0, 'f', 4));
    setChart(d->chart);
    connect(d->chart, &HChromatismChart::plotAreaChanged, this, &HChromatismChartView::handlePlotAreaChanged);
    HZoomChartView::init();
}
