#ifndef HABSTRACTDEVICE_P_H
#define HABSTRACTDEVICE_P_H

#include "HAbstractDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HAbstractDevicePrivate
{
public:
    IPort* port = nullptr;
    int portNum = 1;
    bool portNumScan = true;
    int deviceID = 0x00;
    QMap<HActionType, QList<uchar>> actionParams;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HABSTRACTDEVICE_P_H
