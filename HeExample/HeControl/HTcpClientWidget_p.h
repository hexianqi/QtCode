#pragma once

#include "HTcpClientWidget.h"
#include "HAbstractClientWidget_p.h"

class QTcpSocket;

HE_BEGIN_NAMESPACE

class HTcpClientWidgetPrivate : public HAbstractClientWidgetPrivate
{
public:
    bool connected = false;
    QTcpSocket *socket = nullptr;
};

HE_END_NAMESPACE
