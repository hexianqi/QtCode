#ifndef HRUNTIMESERVICE_P_H
#define HRUNTIMESERVICE_P_H

#include "HRunTimeService.h"
#include <QDateTime>

class QTimer;

HE_CONTROL_BEGIN_NAMESPACE

class HFileLog;

class HRunTimeServicePrivate
{
public:
    HFileLog *fileLog;
    QTimer *timer;
    int lastId;
    QDateTime startTime;
};

HE_CONTROL_END_NAMESPACE

#endif // HRUNTIMESERVICE_P_H
