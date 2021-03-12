#pragma once

#include "HUdpClientWidget.h"
#include "HAbstractClientWidget_p.h"

class QUdpSocket;

HE_CONTROL_BEGIN_NAMESPACE

class HUdpClientWidgetPrivate : public HAbstractClientWidgetPrivate
{
public:
    QUdpSocket *socket = nullptr;
};

HE_CONTROL_END_NAMESPACE
