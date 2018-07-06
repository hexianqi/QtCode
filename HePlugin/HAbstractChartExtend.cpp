#include "HAbstractChartExtend_p.h"

HAbstractChartExtendPrivate::HAbstractChartExtendPrivate(QChart *c)
{
    chart = c;
}

HAbstractChartExtend::HAbstractChartExtend(QChart *chart, QObject *parent)
    : QObject(parent), d_ptr(new HAbstractChartExtendPrivate(chart))
{
}

HAbstractChartExtend::HAbstractChartExtend(HAbstractChartExtendPrivate &p, QObject *parent)
    : QObject(parent), d_ptr(&p)
{
}

HAbstractChartExtend::~HAbstractChartExtend()
{
}
