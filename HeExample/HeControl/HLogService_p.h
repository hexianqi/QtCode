#pragma once

#include "HLogService.h"

HE_BEGIN_NAMESPACE

class HKeepFileLog;

class HLogServicePrivate
{
public:
    HKeepFileLog *fileLog;
    bool toNet = false;
};

HE_END_NAMESPACE
