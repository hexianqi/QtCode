#pragma once

#include "HMultTcpServer.h"

class QTcpSocket;

HE_CONTROL_BEGIN_NAMESPACE

class HMultTcpServerPrivate
{
public:
    QMap<int, QTcpSocket *> clients;
};

HE_CONTROL_END_NAMESPACE
