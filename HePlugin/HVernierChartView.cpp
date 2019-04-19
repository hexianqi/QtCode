#include "HVernierChartView_p.h"
#include "HGraphicsVernierTracking.h"
#include <QtWidgets/QGraphicsSimpleTextItem>

HVernierChartView::HVernierChartView(QWidget *parent) :
    HZoomChartView(*new HVernierChartViewPrivate, nullptr, parent)
{
    init();
}

HVernierChartView::HVernierChartView(QChart *chart, QWidget *parent) :
    HZoomChartView(*new HVernierChartViewPrivate, chart, parent)
{
    init();
}

HVernierChartView::HVernierChartView(HVernierChartViewPrivate &p, QChart *chart, QWidget *parent) :
    HZoomChartView(p, chart, parent)
{
}

HVernierChartView::~HVernierChartView()
{
}

void HVernierChartView::setDecimals(int value)
{
    Q_D(HVernierChartView);
    if (d->decimals == value)
        return;
    d->decimals = value;
    updataVernier();
}

void HVernierChartView::updataVernier()
{
    Q_D(HVernierChartView);
    QList<double> values;
    QStringList texts;
    for (auto vernier : d->tracking->verniers())
    {
        auto point = chart()->mapToValue(vernier);
        auto value = d->tracking->orientation() == Qt::Vertical ? point.x() : point.y();
        values << value;
        texts << QString("%1").arg(value, 0, 'f', d->decimals);
    }
    emit vernierValueChanged(values);
    emit vernierTextChanged(QString("(%1)").arg(texts.join(',')));
}

HGraphicsVernierTracking *HVernierChartView::tracking()
{
    Q_D(HVernierChartView);
    return d->tracking;
}

int HVernierChartView::decimals()
{
    Q_D(HVernierChartView);
    return d->decimals;
}

void HVernierChartView::init()
{
    Q_D(HVernierChartView);
    d->tracking = new HGraphicsVernierTracking(Qt::Vertical, chart(), this);
    d->tracking->resizeVernier(2);
    d->textLeft = new QGraphicsSimpleTextItem(chart());
    d->textLeft->setZValue(100);
    d->textCenter = new QGraphicsSimpleTextItem(chart());
    d->textLeft->setZValue(100);
    d->textRight = new QGraphicsSimpleTextItem(chart());
    d->textLeft->setZValue(100);
    connect(chart(), &QChart::plotAreaChanged, this, &HVernierChartView::handlePlotAreaChanged);
    connect(d->tracking, &HGraphicsVernierTracking::orientationChanged, this, &HVernierChartView::updataVernier);
    connect(d->tracking, &HGraphicsVernierTracking::vernierPosChanged, this, &HVernierChartView::updataVernier);
    connect(d->tracking, &HGraphicsVernierTracking::vernierSizeChanged, this, &HVernierChartView::updataVernier);
    HZoomChartView::init();
}

void HVernierChartView::mousePressEvent(QMouseEvent *e)
{
    Q_D(HVernierChartView);
    if (d->tracking->mousePressEvent(e))
        return;
    HZoomChartView::mousePressEvent(e);
}

void HVernierChartView::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HVernierChartView);
    if (d->tracking->mouseMoveEvent(e))
        return;
    HZoomChartView::mouseMoveEvent(e);
}

void HVernierChartView::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(HVernierChartView);
    if (d->tracking->mouseReleaseEvent(e))
        return;
    HZoomChartView::mouseReleaseEvent(e);
}

void HVernierChartView::handlePlotAreaChanged(QRectF value)
{
    Q_D(HVernierChartView);
    auto y = value.top() + 5;
    d->tracking->setValidRegion(value);
    d->textLeft->setPos(value.left() + 5, y);
    d->textCenter->setPos(value.center().x() - d->textCenter->boundingRect().width() / 2, y);
    d->textRight->setPos(value.right() - d->textRight->boundingRect().width() - 5, y);
    updataVernier();
}
