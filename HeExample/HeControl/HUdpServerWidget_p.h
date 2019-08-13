#ifndef HUDPSERVERWIDGET_P_H
#define HUDPSERVERWIDGET_P_H

#include "HUdpServerWidget.h"
#include "HAbstractNetworkWidget_p.h"

class QUdpSocket;

HE_CONTROL_BEGIN_NAMESPACE

class HUdpServerWidgetPrivate : public HAbstractNetworkWidgetPrivate
{
public:
    HUdpServerWidgetPrivate();

public:
    QString serverIp;
    int serverPort = 6000;
    int listenPort = 6000;
    int currentCount = 0;
    int maxCount = 100;
    QUdpSocket *udpSocket;
};

HE_CONTROL_END_NAMESPACE

#endif // HUDPSERVERWIDGET_P_H
