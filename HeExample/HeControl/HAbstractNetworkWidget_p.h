#pragma once

#include "HAbstractNetworkWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractNetworkWidgetPrivate
{
public:
    bool hexSend = false;
    bool hexReceive = false;
    bool ascii = false;
    bool autoSend = false;
    int interval = 1000;
    int currentCount = 0;
    int maxCount = 100;

public:
    QTimer *timer;
};

HE_CONTROL_END_NAMESPACE
