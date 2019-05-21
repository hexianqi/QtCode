#include "HChromatismChartView_p.h"
#include "HChromatismChart.h"
#include "HPluginHelper.h"
#include <QtCore/QJsonObject>

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

HChromatismChartView::~HChromatismChartView()
{
}

void HChromatismChartView::setData(QJsonObject json)
{
    Q_D(HChromatismChartView);
    if (json.contains("title"))
        d->chart->setTitle(json.value("title").toString());
    if (json.contains("stdSdcm"))
        d->stdSdcm = json.value("stdSdcm").toDouble();
    if (json.contains("pointCenterX"))
        d->pointCenter.setX(json.value("pointCenterX").toDouble());
    if (json.contains("pointCenterY"))
        d->pointCenter.setY(json.value("pointCenterY").toDouble());
    if (json.contains("stdTheta"))
        d->stdTheta = json.value("stdTheta").toDouble();
    if (json.contains("stdA"))
        d->stdA = json.value("stdA").toDouble();
    if (json.contains("stdB"))
        d->stdB = json.value("stdB").toDouble();
    if (json.contains("pointFocusX"))
        d->pointFocus.setX(json.value("pointFocusX").toDouble());
    if (json.contains("pointFocusY"))
        d->pointFocus.setY(json.value("pointFocusY").toDouble());
    if (json.contains("sdcm"))
        d->sdcm = json.value("sdcm").toDouble();

    d->chart->setEllipse(HPluginHelper::calcEllipse(d->pointCenter, d->stdSdcm, d->stdTheta, d->stdA, d->stdB));
    d->chart->setPointCenter(d->pointCenter);
    d->chart->setPointFocus(d->pointFocus);
    d->chart->createDefaultAxes();
    d->chart->setAxesXTitle(tr("标准 %1SDCM - 目标值x=%2,y=%3").arg(d->stdSdcm, 0, 'f', 1).arg(d->pointCenter.x(), 0, 'f', 3).arg(d->pointCenter.y(), 0, 'f', 3));
    d->pointFocusItem->setText(tr("(%2, %3)\n      %1SDCM").arg(d->sdcm, 0, 'f', 1).arg(d->pointFocus.x(), 0, 'f', 4).arg(d->pointFocus.y(), 0, 'f', 4));
}

void HChromatismChartView::init()
{
    Q_D(HChromatismChartView);
    d->chart = new HChromatismChart;
    d->pointFocusItem = new QGraphicsSimpleTextItem(d->chart);
    d->pointFocusItem->setPen(QPen(Qt::red));
    d->pointFocusItem->setZValue(100);
    d->pointFocusItem->setText(tr("(%2, %3)\n      %1SDCM").arg(d->sdcm, 0, 'f', 1).arg(d->pointFocus.x(), 0, 'f', 4).arg(d->pointFocus.y(), 0, 'f', 4));
    setChart(d->chart);
    connect(d->chart, &HChromatismChart::plotAreaChanged, this, &HChromatismChartView::handlePlotAreaChanged);
    HZoomChartView::init();
}
