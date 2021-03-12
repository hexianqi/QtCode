#pragma once

#include "HAbstractPort_p.h"
#include "HSerialPort.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HSerialPortPrivate : public HAbstractPortPrivate
{
public:
    ulong baudRate = 115200;
    void *handle = nullptr;
};

HE_COMMUNICATE_END_NAMESPACE
