#pragma once

#include "HAbstractPort_p.h"
#include "HSerialPort.h"

HE_BEGIN_NAMESPACE

class HSerialPortPrivate : public HAbstractPortPrivate
{
public:
    ulong baudRate = 115200;
    uchar parity = 0;
    void *handle = nullptr;
};

HE_END_NAMESPACE
