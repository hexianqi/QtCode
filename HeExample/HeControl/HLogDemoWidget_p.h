#pragma once

#include "HLogDemoWidget.h"

HE_BEGIN_NAMESPACE

class HLogRedirectService;
class HLogNetworkService;
class HKeepLogFile;

class HLogDemoWidgetPrivate
{
public:
    HLogRedirectService *logRedirectService = nullptr;
    HLogNetworkService *logNetworkService = nullptr;
    HKeepLogFile *logFile = nullptr;
    QTimer *timer = nullptr;
    int count = 0;
};

HE_END_NAMESPACE
