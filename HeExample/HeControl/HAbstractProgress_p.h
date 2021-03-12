#pragma once

#include "HAbstractProgress.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractProgressPrivate
{
public:
    double minimum = 0.0;
    double maximum = 100.0;
    double value = 0.0;
    int decimal = 0;
};

HE_CONTROL_END_NAMESPACE
