#include "HAbstractSimulateDevice_p.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

HAbstractSimulateDevice::HAbstractSimulateDevice() :
    HAbstractDevice(*new HAbstractSimulateDevicePrivate)
{
}

HAbstractSimulateDevice::HAbstractSimulateDevice(HAbstractSimulateDevicePrivate &p) :
    HAbstractDevice(p)
{
}

bool HAbstractSimulateDevice::open()
{
    return true;
}

bool HAbstractSimulateDevice::close()
{
    return true;
}

HE_COMMUNICATE_END_NAMESPACE
