#pragma once

#include "HAbstractDevice.h"

HE_BEGIN_NAMESPACE

class HAbstractDevicePrivate
{
public:
    IPort *port = nullptr;
    int portNum = 1;
    bool portNumScan = true;
    int deviceID = 0x00;
    QMap<HActionType, QList<uchar>> actionParams;
};

HE_END_NAMESPACE
