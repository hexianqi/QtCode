#include "HAbstractChartExtend_p.h"

HAbstractChartExtendPrivate::HAbstractChartExtendPrivate(QChart *c)
{
    chart = c;
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

HAbstractChartExtend::~HAbstractChartExtend()
{
}

void HAbstractChartExtend::setChart(QChart *c)
{
    if (d_ptr->chart == c)
        return;
    disconnectExtend();
    d_ptr->chart = c;
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
