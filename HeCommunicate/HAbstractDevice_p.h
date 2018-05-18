#ifndef HABSTRACTDEVICE_P_H
#define HABSTRACTDEVICE_P_H

#include "HAbstractDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HAbstractDevicePrivate
{
public:
    IPort* port = nullptr;
    int portNum;
    bool portNumScan;
    int deviceID;
    QHash<HActionType, QList<uchar>> actionParam;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HABSTRACTDEVICE_P_H
