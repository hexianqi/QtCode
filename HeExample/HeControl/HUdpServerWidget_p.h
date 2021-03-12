#pragma once

#include "HUdpServerWidget.h"
#include "HAbstractServerWidget_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HUdpServer;

class HUdpServerWidgetPrivate : public HAbstractServerWidgetPrivate
{
public:
    HUdpServer *server = nullptr;
};

HE_CONTROL_END_NAMESPACE
