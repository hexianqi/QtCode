#include "HCalloutChartExtend_p.h"
#include "HCalloutChartItem.h"
#include <QtCharts/QChart>
#include <QtCharts/QXYSeries>
#include <QtWidgets/QAction>

HCalloutChartExtend::HCalloutChartExtend(QObject *parent) :
    HAbstractChartExtend(*new HCalloutChartExtendPrivate, parent)
{
    init();
}

HCalloutChartExtend::HCalloutChartExtend(QChart *chart, QObject *parent) :
    HAbstractChartExtend(*new HCalloutChartExtendPrivate(chart), parent)
{
    init();
}

HCalloutChartExtend::HCalloutChartExtend(HCalloutChartExtendPrivate &p, QObject *parent) :
    HAbstractChartExtend(p, parent)
{
}

bool HCalloutChartExtend::connectExtend()
{
    if (!HAbstractChartExtend::connectExtend())
        return false;

    foreachSeries([=](QAbstractSeries *p) { connectSeries(p); });
    return true;
}

bool HCalloutChartExtend::disconnectExtend()
{
    if (!HAbstractChartExtend::disconnectExtend())
        return false;

    foreachSeries([=](QAbstractSeries *p) { disconnectSeries(p); });
    return true;
}

void HCalloutChartExtend::connectSeries(QAbstractSeries *p)
{
    auto s = qobject_cast<QXYSeries *>(p);
    if (s == nullptr)
        return;

    // Disconnect possible existing connection to avoid multiple connections
    disconnect(s, &QXYSeries::clicked, this, &HCalloutChartExtend::handleSeriesClicked);
    disconnect(s, &QXYSeries::hovered, this, &HCalloutChartExtend::handleSeriesHovered);
    connect(s, &QXYSeries::clicked, this, &HCalloutChartExtend::handleSeriesClicked);
    connect(s, &QXYSeries::hovered, this, &HCalloutChartExtend::handleSeriesHovered);
}

void HCalloutChartExtend::disconnectSeries(QAbstractSeries *p)
{
    auto s = qobject_cast<QXYSeries *>(p);
    if (s == nullptr)
        return;
    disconnect(s, &QXYSeries::clicked, this, &HCalloutChartExtend::handleSeriesClicked);
    disconnect(s, &QXYSeries::hovered, this, &HCalloutChartExtend::handleSeriesHovered);
}

void HCalloutChartExtend::updateGeometry()
{
    Q_D(HCalloutChartExtend);
    for (auto i : d->callouts)
        i->updateGeometry();
}

void HCalloutChartExtend::clear()
{
    Q_D(HCalloutChartExtend);
    qDeleteAll(d->callouts);
    d->callouts.clear();
}

void HCalloutChartExtend::handleSeriesClicked(QPointF /*point*/)
{
    Q_D(HCalloutChartExtend);
    d->callouts.append(d->tooltip);
    d->tooltip = nullptr;
}

void HCalloutChartExtend::handleSeriesHovered(QPointF point, bool state)
{
    Q_D(HCalloutChartExtend);
    if (d->tooltip == nullptr)
        d->tooltip = new HCalloutChartItem(d->chart);

    if (state)
    {
        d->tooltip->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));
        d->tooltip->setAnchor(point);
        d->tooltip->setZValue(11);
        d->tooltip->updateGeometry();
        d->tooltip->show();
    }
    else
        d->tooltip->hide();
}

void HCalloutChartExtend::init()
{
    Q_D(HCalloutChartExtend);
    auto clear = new QAction(QIcon(":/image/Annotation.png"), tr("清除标注(&C)"), this);
    connect(clear, &QAction::triggered, this, &HCalloutChartExtend::clear);
    d->actions.append(clear);
}
