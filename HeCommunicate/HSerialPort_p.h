#ifndef HSERIALPORT_P_H
#define HSERIALPORT_P_H

#include "HAbstractPort_p.h"
#include "HSerialPort.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HSerialPortPrivate : public HAbstractPortPrivate
{    
public:
    ulong baudRate = 115200;
    void *hDevice = nullptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HSERIALPORT_P_H
