#ifndef HTCPSERVERWIDGET_P_H
#define HTCPSERVERWIDGET_P_H

#include "HTcpServerWidget.h"
#include "HAbstractNetworkWidget_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HTcpServer;

class HTcpServerWidgetPrivate : public HAbstractNetworkWidgetPrivate
{
public:
    HTcpServerWidgetPrivate();

public:
    int listenPort = 6000;
    bool connect = false;
    int currentCount = 0;
    int maxCount = 100;
    HTcpServer *tcpServer;
};

HE_CONTROL_END_NAMESPACE

#endif // HTCPSERVERWIDGET_P_H
