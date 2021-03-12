#pragma once

#include "HCalloutChartExtend.h"
#include "HAbstractChartExtend_p.h"

class HCalloutChartItem;

class HCalloutChartExtendPrivate : public HAbstractChartExtendPrivate
{
public:
    using HAbstractChartExtendPrivate::HAbstractChartExtendPrivate;

public:
    HCalloutChartItem *tooltip = nullptr;
    QList<HCalloutChartItem *> callouts;
};
