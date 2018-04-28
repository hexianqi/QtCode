#ifndef HSERIALPORT_P_H
#define HSERIALPORT_P_H

#include "HAbstractPort_p.h"
#include "HSerialPort.h"

class QSerialPort;

HE_COMMUNICATE_BEGIN_NAMESPACE

class HSerialPortPrivate : public HAbstractPortPrivate
{
public:
    bool openSerialPort(int portNum, QObject *parent);

public:
    qint32 baudRate = 115200;
    QSerialPort *serial;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HSERIALPORT_P_H
