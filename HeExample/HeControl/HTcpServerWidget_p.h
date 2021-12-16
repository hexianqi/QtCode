#pragma once

#include "HTcpServerWidget.h"
#include "HAbstractServerWidget_p.h"

HE_BEGIN_NAMESPACE

class HTcpServer;

class HTcpServerWidgetPrivate : public HAbstractServerWidgetPrivate
{
public:
    HTcpServer *server = nullptr;
};

HE_END_NAMESPACE
