#pragma once

#include "HUdpClientWidget.h"
#include "HAbstractClientWidget_p.h"

class QUdpSocket;

HE_BEGIN_NAMESPACE

class HUdpClientWidgetPrivate : public HAbstractClientWidgetPrivate
{
public:
    QUdpSocket *socket = nullptr;
};

HE_END_NAMESPACE
