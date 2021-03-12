#pragma once

#include "HPositionTracking.h"
#include "HAbstractMouseStrategy_p.h"

class HPositionTrackingPrivate : public HAbstractMouseStrategyPrivate
{
public:
    HPositionTrackingPrivate(QWidget *p);
};
