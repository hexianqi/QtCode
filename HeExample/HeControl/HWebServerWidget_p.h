#pragma once

#include "HWebServerWidget.h"
#include "HAbstractServerWidget_p.h"

HE_BEGIN_NAMESPACE

class HWebServer;

class HWebServerWidgetPrivate : public HAbstractServerWidgetPrivate
{
public:
    HWebServer *server = nullptr;
};

HE_END_NAMESPACE

