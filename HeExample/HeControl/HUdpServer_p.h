#pragma once

#include "HUdpServer.h"
#include <QtCore/QSet>

class QUdpSocket;

HE_BEGIN_NAMESPACE

class HUdpServerPrivate
{
public:
    bool isRunning = false;
    QString listenAddress = "0.0.0.0";
    int listenPort = 6000;
    QSet<QString> clients;
    QUdpSocket *socket;
};

HE_END_NAMESPACE
