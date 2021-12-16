#pragma once

#include "HTcpServer.h"

HE_BEGIN_NAMESPACE

class HTcpClient;

class HTcpServerPrivate
{
public:
    QString listenAddress = "0.0.0.0";
    int listenPort = 6000;
    QMap<QString, HTcpClient *> clients;
};

HE_END_NAMESPACE
