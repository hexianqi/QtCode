#ifndef HPOSITIONTRACKING_P_H
#define HPOSITIONTRACKING_P_H

#include "HPositionTracking.h"

class HPositionTrackingPrivate
{
public:
    bool enableTracking = true;
    QRectF validRegion;
};

#endif // HPOSITIONTRACKING_P_H
