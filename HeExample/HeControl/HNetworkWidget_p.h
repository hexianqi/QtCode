#pragma once

#include "HNetworkWidget.h"

class QTabWidget;

HE_BEGIN_NAMESPACE

class HTcpClientWidget;
class HTcpServerWidget;
class HUdpClientWidget;
class HUdpServerWidget;

class HNetworkWidgetPrivate
{
public:
    QTabWidget *tabWidget;
    HTcpClientWidget *tcpClient;
    HTcpServerWidget *tcpServer;
    HUdpClientWidget *udpClient;
    HUdpServerWidget *udpServer;
};

HE_END_NAMESPACE
