#pragma once

#include "HNetworkLog.h"

class QTcpSocket;
class QTcpServer;

HE_BEGIN_NAMESPACE

class HNetworkLogPrivate
{
public:
    QTcpSocket *socket;
    QTcpServer *server;
};

HE_END_NAMESPACE
