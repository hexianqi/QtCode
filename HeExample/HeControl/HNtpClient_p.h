#pragma once

#include "HNtpClient.h"

class QUdpSocket;

HE_BEGIN_NAMESPACE

class HNtpClientPrivate
{
public:
    QString host;
    QUdpSocket *socket;
};

HE_END_NAMESPACE
