#pragma once

#include "HWebClientWidget.h"
#include "HAbstractClientWidget_p.h"

class QWebSocket;

HE_BEGIN_NAMESPACE

class HWebClientWidgetPrivate : public HAbstractClientWidgetPrivate
{
public:
    HWebClientWidgetPrivate();

public:
    bool connected = false;
    QWebSocket *socket = nullptr;
};

HE_END_NAMESPACE

