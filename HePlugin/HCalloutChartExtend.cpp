#include "HCalloutChartExtend_p.h"
#include "HCalloutChartItem.h"
#include <QtCharts/QChart>
#include <QtCharts/QXYSeries>

HCalloutChartExtend::HCalloutChartExtend(QObject *parent) :
    HAbstractChartExtend(*new HCalloutChartExtendPrivate, parent)
{
}

HCalloutChartExtend::HCalloutChartExtend(QChart *chart, QObject *parent) :
    HAbstractChartExtend(*new HCalloutChartExtendPrivate(chart), parent)
{
}

HCalloutChartExtend::HCalloutChartExtend(HCalloutChartExtendPrivate &p, QObject *parent) :
    HAbstractChartExtend(p, parent)
{
}

bool HCalloutChartExtend::connectExtend()
{
    if (!HAbstractChartExtend::connectExtend())
        return false;

    auto series = chart()->series();
    for (auto s : series)
    {
        auto ss = qobject_cast<QXYSeries *>(s);
        if (ss == nullptr)
            continue;
        connectExtend(ss);
    }
    return true;
}

void HCalloutChartExtend::connectExtend(QXYSeries *s)
{
    // Disconnect possible existing connection to avoid multiple connections
    disconnect(s, &QXYSeries::clicked, this, &HCalloutChartExtend::handleSeriesClicked);
    disconnect(s, &QXYSeries::hovered, this, &HCalloutChartExtend::handleSeriesHovered);
    connect(s, &QXYSeries::clicked, this, &HCalloutChartExtend::handleSeriesClicked);
    connect(s, &QXYSeries::hovered, this, &HCalloutChartExtend::handleSeriesHovered);
}

bool HCalloutChartExtend::disconnectExtend()
{
    if (!HAbstractChartExtend::disconnectExtend())
        return false;

    auto series = chart()->series();
    for (auto s : series)
    {
        auto ss = qobject_cast<QXYSeries *>(s);
        if (ss == nullptr)
            continue;
        disconnectExtend(ss);
    }
    return true;
}

void HCalloutChartExtend::disconnectExtend(QXYSeries *s)
{
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
