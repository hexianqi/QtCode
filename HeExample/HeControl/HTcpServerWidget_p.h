#pragma once

#include "HTcpServerWidget.h"
#include "HAbstractServerWidget_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HTcpServer;

class HTcpServerWidgetPrivate : public HAbstractServerWidgetPrivate
{
public:
    HTcpServer *server = nullptr;
};

HE_CONTROL_END_NAMESPACE
