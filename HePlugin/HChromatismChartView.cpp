#include "HChromatismChartView_p.h"
#include "HSingleAxisChart.h"
#include "HDrawHelper.h"
#include "HeAlgorithm/HMath.h"
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>

HE_USE_NAMESPACE

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
    {
        QList<double> c;
        for (const auto &v : value.value("[中心点]").toList())
            c << v.toDouble();
        d->pointCenter = QPointF(c[0], c[1]);
    }
    if (value.contains("[旋转角]"))
        d->theta = value.value("[旋转角]").toDouble();
    if (value.contains("[轴A]"))
        d->axisA = value.value("[轴A]").toDouble();
    if (value.contains("[轴B]"))
        d->axisB = value.value("[轴B]").toDouble();
    if (value.contains("[测试点]"))
    {
        QList<double> c;
        for (const auto &v : value.value("[测试点]").toList())
            c << v.toDouble();
        d->pointFocus = QPointF(c[0], c[1]);
    }
    if (value.contains("[测试Sdcm]"))
        d->sdcmFocus = value.value("[测试Sdcm]").toDouble();

    d->ellipse->replace(HMath::calcEllipse(d->pointCenter, d->sdcmStd, d->theta, d->axisA, d->axisB));
    d->center->replace(0, d->pointCenter);
    d->focus->replace(0, d->pointFocus);
    d->axisX->setTitleText(tr("标准%1SDCM - x=%2,y=%3").arg(d->sdcmStd, 0, 'f', 1).arg(d->pointCenter.x(), 0, 'f', 3).arg(d->pointCenter.y(), 0, 'f', 3));
    d->pointFocusItem->setText(tr("%2, %3\n      %1SDCM").arg(d->sdcmFocus, 0, 'f', 1).arg(d->pointFocus.x(), 0, 'f', 4).arg(d->pointFocus.y(), 0, 'f', 4));
    fixAxes();
}

void HChromatismChartView::init()
{
    Q_D(HChromatismChartView);
    HZoomChartView::init();
    auto f = font();
    f.setPixelSize(15);
    f.setBold(true);
    d->ellipse = new QLineSeries;
    d->focus = new QScatterSeries;
    d->focus->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    d->focus->setMarkerSize(11.0);
    d->focus->setPen(QColor(Qt::transparent));
    d->focus->setBrush(HDrawHelper::createCrossImage(QSize(9, 9), QPen(Qt::red, 2)));
    d->focus->append(0.5, 0.5);
    d->center = new QScatterSeries();
    d->center->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    d->center->setMarkerSize(10.0);
    d->center->append(0.5, 0.5);
    d->axisX = new QValueAxis;
    d->axisX->setRange(0, 1);
    d->axisX->setTickCount(6);
    d->axisY = new QValueAxis;
    d->axisY->setRange(0, 1);
    d->axisY->setTickCount(6);
    d->chart = new HSingleAxisChart;
    d->chart->setAxisX(d->axisX);
    d->chart->setAxisY(d->axisY);
    d->chart->addSeries(d->ellipse);
    d->chart->addSeries(d->focus);
    d->chart->addSeries(d->center);
    d->chart->setTitleFont(f);
    d->chart->legend()->hide();
    d->pointFocusItem = new QGraphicsSimpleTextItem(d->chart);
    d->pointFocusItem->setPen(QPen(Qt::red));
    d->pointFocusItem->setZValue(100);
    d->pointFocusItem->setText(tr("%2, %3\n      %1SDCM").arg(d->sdcmFocus, 0, 'f', 1).arg(d->pointFocus.x(), 0, 'f', 4).arg(d->pointFocus.y(), 0, 'f', 4));
    fixAxes();
    setChart(d->chart);
    connect(d->chart, &HSingleAxisChart::plotAreaChanged, this, &HChromatismChartView::handlePlotAreaChanged);
}

void HChromatismChartView::fixAxes()
{
    Q_D(HChromatismChartView);
    auto x1 = d->center->at(0).x();
    auto x2 = d->center->at(0).x();
    auto y1 = d->center->at(0).y();
    auto y2 = d->center->at(0).y();
    for (auto p : d->ellipse->points())
    {
        x1 = qMin(x1, p.x());
        x2 = qMax(x2, p.x());
        y1 = qMin(y1, p.y());
        y2 = qMax(y2, p.y());
    }
    x1 = int((x1 - 0.005) * 500) / 500.0;
    x2 = int((x2 + 0.005) * 500) / 500.0;
    y1 = int((y1 - 0.005) * 500) / 500.0;
    y2 = int((y2 + 0.005) * 500) / 500.0;
    d->axisX->setRange(x1, x2);
    d->axisY->setRange(y1, y2);
}
