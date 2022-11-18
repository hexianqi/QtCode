#pragma once

#include "HTimeSlider.h"

HE_BEGIN_NAMESPACE

class HTimeSliderPrivate
{
public:
    int sec = 600;
    int currentSec = 0;
    QRect textRect;
    bool isPress = false;
};

HE_END_NAMESPACE

