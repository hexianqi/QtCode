#pragma once

#include "HRunTimeService.h"
#include <QDateTime>

class QTimer;

HE_BEGIN_NAMESPACE

class HFileLog;

class HRunTimeServicePrivate
{
public:
    HFileLog *fileLog;
    QTimer *timer;
    int lastId;
    QDateTime startTime;
};

HE_END_NAMESPACE
