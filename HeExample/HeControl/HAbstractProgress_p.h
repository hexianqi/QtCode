#pragma once

#include "HAbstractProgress.h"

HE_BEGIN_NAMESPACE

class HAbstractProgressPrivate
{
public:
    double minimum = 0.0;
    double maximum = 100.0;
    double value = 0.0;
    int decimal = 0;
};

HE_END_NAMESPACE
