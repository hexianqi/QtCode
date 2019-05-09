#ifndef HCALLOUTCHARTEXTEND_P_H
#define HCALLOUTCHARTEXTEND_P_H

#include "HCalloutChartExtend.h"
#include "HAbstractChartExtend_p.h"

class HGraphicsCalloutItem;

class HCalloutChartExtendPrivate : public HAbstractChartExtendPrivate
{
public:
    using HAbstractChartExtendPrivate::HAbstractChartExtendPrivate;

public:
    HGraphicsCalloutItem *tooltip = nullptr;
    QList<HGraphicsCalloutItem *> callouts;
};

#endif // HCALLOUTCHARTEXTEND_P_H
