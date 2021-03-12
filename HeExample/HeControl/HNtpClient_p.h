#pragma once

#include "HNtpClient.h"

class QUdpSocket;

HE_CONTROL_BEGIN_NAMESPACE

class HNtpClientPrivate
{
public:
    QString host;
    QUdpSocket *socket;
};

HE_CONTROL_END_NAMESPACE
