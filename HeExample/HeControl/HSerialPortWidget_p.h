#ifndef HSERIALPORTWIDGET_P_H
#define HSERIALPORTWIDGET_P_H

#include "HSerialPortWidget.h"

class QSerialPort;

HE_CONTROL_BEGIN_NAMESPACE

class HSerialPortWidgetPrivate
{
public:
    QTimer *timeTimer;
    QTimer *readTimer;
    QTimer *sendTimer;
    QTimer *saveTimer;
    bool isConnected = false;
    bool isShow = true;
    int sendCount = 0;
    int sendTimes = 0;
    int receiveCount = 0;
    int receiveTimes = 0;
    QSerialPort *port;
    int timeOut = 200;
    int readInterval = 200;
    int sendInterval = 200;
};

HE_CONTROL_END_NAMESPACE

#endif // HSERIALPORTWIDGET_P_H
