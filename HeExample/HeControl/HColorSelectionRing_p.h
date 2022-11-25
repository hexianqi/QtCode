#pragma once

#include "HColorSelectionRing.h"

HE_BEGIN_NAMESPACE

class HColorSelectionRingPrivate
{
public:
    double ballAngle = 0;
    bool isPressed = false;
    QConicalGradient conicalGradient;
};

HE_END_NAMESPACE

