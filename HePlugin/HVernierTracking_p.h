#ifndef HVERNIERTRACKING_P_H
#define HVERNIERTRACKING_P_H

#include "HVernierTracking.h"
#include "HAbstractVernierTracking_p.h"

class HVernierTrackingPrivate : public HAbstractVernierTrackingPrivate
{
public:
    HVernierTrackingPrivate(Qt::Orientation o, QWidget *p);
};

#endif // HVERNIERTRACKING_P_H
