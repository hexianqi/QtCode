#pragma once

#include "HLogService.h"

HE_CONTROL_BEGIN_NAMESPACE

class HKeepFileLog;

class HLogServicePrivate
{
public:
    HKeepFileLog *fileLog;
    bool toNet = false;
};

HE_CONTROL_END_NAMESPACE
