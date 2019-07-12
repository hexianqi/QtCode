#ifndef HMULTTCPSERVER_P_H
#define HMULTTCPSERVER_P_H

#include "HMultTcpServer.h"

class QTcpSocket;

HE_CONTROL_BEGIN_NAMESPACE

class HMultTcpServerPrivate
{
public:
    QMap<int, QTcpSocket *> clients;
};

HE_CONTROL_END_NAMESPACE

#endif // HMULTTCPSERVER_P_H
