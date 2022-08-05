#pragma once

#include "HWebServer.h"

HE_BEGIN_NAMESPACE

class HWebClient;

class HWebServerPrivate
{
public:
    QString listenAddress = "0.0.0.0";
    int listenPort = 6000;
    QMap<QString, HWebClient *> clients;
};

HE_END_NAMESPACE

