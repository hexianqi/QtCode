#ifndef HPOSITIONTRACKING_P_H
#define HPOSITIONTRACKING_P_H

#include "HPositionTracking.h"
#include "HAbstractMouseStrategy_p.h"

class HPositionTrackingPrivate : public HAbstractMouseStrategyPrivate
{
public:
    HPositionTrackingPrivate(QWidget *p);

public:
    IPositionTrackingControl *control;
};

#endif // HPOSITIONTRACKING_P_H
