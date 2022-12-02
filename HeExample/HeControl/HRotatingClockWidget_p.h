#pragma once

#include "HRotatingClockWidget.h"

HE_BEGIN_NAMESPACE

class HRotatingClockWidgetPrivate
{
public:
    QTimer *secondTimer;
    QTimer *animationTimer;
    int secondOnePlace = 0;
    int secondTenPlace = 0;
    int minuteOnePlace = 0;
    int minuteTenPlace = 0;
    int hourOnePlace = 0;
    int hourTenPlace = 0;
    int secondOnePlaceRotate = 0;
    int secondTenPlaceRotate = -1;
    int minuteOnePlaceRotate = -1;
    int minuteTenPlaceRotate = -1;
    int hourOnePlaceRotate = -1;
    int hourTenPlaceRotate = -1;
};

HE_END_NAMESPACE

