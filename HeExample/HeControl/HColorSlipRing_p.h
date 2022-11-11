#pragma once

#include "HColorSlipRing.h"

HE_BEGIN_NAMESPACE

class HColorSlipRingPrivate
{
public:
    QPoint pressPos;
    bool isPressed;
    double ballAngle = 0;
};

HE_END_NAMESPACE

