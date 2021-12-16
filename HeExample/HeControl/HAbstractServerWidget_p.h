#pragma once

#include "HAbstractServerWidget.h"
#include "HAbstractNetworkWidget_p.h"

HE_BEGIN_NAMESPACE

class HAbstractServerWidgetPrivate : public HAbstractNetworkWidgetPrivate
{
public:
    QString listenAddress = "127.0.0.1";
    int listenPort = 6000;
};

HE_END_NAMESPACE
