#ifndef HTCPSERVER_P_H
#define HTCPSERVER_P_H

#include "HTcpServer.h"

HE_CONTROL_BEGIN_NAMESPACE

class HTcpClient;

class HTcpServerPrivate
{
public:
    QString listenAddress = "0.0.0.0";
    int listenPort = 6000;
    QMap<QString, HTcpClient *> clients;
};

HE_CONTROL_END_NAMESPACE

#endif // HTCPSERVER_P_H
