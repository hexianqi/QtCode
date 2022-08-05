#pragma once

#include "HWebClient.h"

HE_BEGIN_NAMESPACE

class HWebClientPrivate
{
public:
    QWebSocket *socket = nullptr;
};

HE_END_NAMESPACE

