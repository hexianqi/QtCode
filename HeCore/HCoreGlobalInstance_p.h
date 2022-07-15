#pragma once

#include "HCoreGlobalInstance.h"

HE_BEGIN_NAMESPACE

class HLogRedirectService;
class HKeepLogFile;

class HCoreGlobalInstancePrivate
{
public:
    bool initialized = false;
    HLogRedirectService *logService = nullptr;
    HKeepLogFile *logFile = nullptr;
};

HE_END_NAMESPACE
