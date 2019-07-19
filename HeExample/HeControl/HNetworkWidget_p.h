#ifndef HNETWORKWIDGET_P_H
#define HNETWORKWIDGET_P_H

#include "HNetworkWidget.h"

class QTabWidget;

HE_CONTROL_BEGIN_NAMESPACE

class HTcpClientWidget;
class HTcpServerWidget;
class HUdpServerWidget;

class HNetworkWidgetPrivate
{
public:
    QTabWidget *tabWidget;
    HTcpClientWidget *tcpClient;
    HTcpServerWidget *tcpServer;
    HUdpServerWidget *udpServer;
};

HE_CONTROL_END_NAMESPACE

#endif // HNETWORKWIDGET_P_H
