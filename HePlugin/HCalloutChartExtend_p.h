#ifndef HCALLOUTCHARTEXTEND_P_H
#define HCALLOUTCHARTEXTEND_P_H

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

#endif // HCALLOUTCHARTEXTEND_P_H
