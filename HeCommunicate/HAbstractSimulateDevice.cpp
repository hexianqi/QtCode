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

HErrorType HAbstractSimulateDevice::open()
{
    return E_OK;
}

HErrorType HAbstractSimulateDevice::close()
{
    return E_OK;
}

HE_COMMUNICATE_END_NAMESPACE
