#ifndef HLOGSERVICE_P_H
#define HLOGSERVICE_P_H

#include "HLogService.h"

HE_CONTROL_BEGIN_NAMESPACE

class HKeepFileLog;

class HLogServicePrivate
{
public:
    HKeepFileLog *log;
    bool toNet = false;
};

HE_CONTROL_END_NAMESPACE

#endif // HLOGSERVICE_P_H
