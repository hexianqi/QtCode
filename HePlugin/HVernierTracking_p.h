#pragma once

#include "HVernierTracking.h"
#include "HAbstractVernierTracking_p.h"

class HVernierTrackingPrivate : public HAbstractVernierTrackingPrivate
{
public:
    HVernierTrackingPrivate(Qt::Orientation o, QWidget *p);
};
