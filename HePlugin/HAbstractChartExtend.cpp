#include "HAbstractChartExtend_p.h"
#include <QtCharts/QChart>
#include <QtCharts/QLegendMarker>

HAbstractChartExtendPrivate::HAbstractChartExtendPrivate(QChart *p)
{
    chart = p;
}

HAbstractChartExtend::HAbstractChartExtend(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractChartExtendPrivate)
{
}

HAbstractChartExtend::HAbstractChartExtend(QChart *chart, QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractChartExtendPrivate(chart))
{
}

HAbstractChartExtend::HAbstractChartExtend(HAbstractChartExtendPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractChartExtend::~HAbstractChartExtend() = default;

QList<QAction *> HAbstractChartExtend::actions()
{
    return d_ptr->actions;
}

void HAbstractChartExtend::setChart(QChart *p)
{
    if (d_ptr->chart == p)
        return;
    disconnectExtend();
    d_ptr->chart = p;
    connectExtend();
}

QChart *HAbstractChartExtend::chart()
{
    return d_ptr->chart;
}

bool HAbstractChartExtend::connectExtend()
{
    return chart() != nullptr;
}

bool HAbstractChartExtend::disconnectExtend()
{
    return chart() != nullptr;
}

void HAbstractChartExtend::foreachMarker(const std::function<void(QLegendMarker *)> &func)
{
    auto markers = chart()->legend()->markers();
    for (auto m : markers)
        func(m);
}

void HAbstractChartExtend::foreachSeries(const std::function<void(QAbstractSeries *)> &func)
{
    auto series = chart()->series();
    for (auto s : series)
        func(s);
}
