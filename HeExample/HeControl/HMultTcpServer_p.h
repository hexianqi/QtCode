#pragma once

#include "HMultTcpServer.h"

class QTcpSocket;

HE_BEGIN_NAMESPACE

class HMultTcpServerPrivate
{
public:
    QMap<int, QTcpSocket *> clients;
};

HE_END_NAMESPACE
