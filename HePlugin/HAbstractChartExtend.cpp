#include "HAbstractChartExtend_p.h"

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
