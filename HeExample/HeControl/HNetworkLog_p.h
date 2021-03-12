#pragma once

#include "HNetworkLog.h"

class QTcpSocket;
class QTcpServer;

HE_CONTROL_BEGIN_NAMESPACE

class HNetworkLogPrivate
{
public:
    QTcpSocket *socket;
    QTcpServer *server;
};

HE_CONTROL_END_NAMESPACE
