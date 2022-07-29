#pragma once

#include "HTcpClient.h"

HE_BEGIN_NAMESPACE

class HTcpClientPrivate
{
public:
    QTcpSocket *socket = nullptr;
};

HE_END_NAMESPACE
