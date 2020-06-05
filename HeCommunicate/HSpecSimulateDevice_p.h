#pragma once

#include "HSpecSimulateDevice.h"
#include "HAbstractSimulateDevice_p.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HSpecSimulateDevicePrivate : public HAbstractSimulateDevicePrivate
{
public:
    double intergalTime = 1;
};

HE_COMMUNICATE_END_NAMESPACE

