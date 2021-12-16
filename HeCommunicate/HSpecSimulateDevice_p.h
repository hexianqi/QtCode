#pragma once

#include "HSpecSimulateDevice.h"
#include "HAbstractDevice_p.h"

HE_BEGIN_NAMESPACE

class HSpecSimulateDevicePrivate : public HAbstractDevicePrivate
{
public:
    double intergalTime = 1;
};

HE_END_NAMESPACE

