#ifndef HRUNTIMESERVICE_P_H
#define HRUNTIMESERVICE_P_H

#include "HRunTimeService.h"
#include <QDateTime>

class QTimer;

HE_CONTROL_BEGIN_NAMESPACE

class HRunTimeServicePrivate
{
public:
    HRunTimeServicePrivate();

public:
    QTimer *timer;
    QString path;
    QString fileName;
    int interval;
    int lastId;
    QDateTime startTime;
};

HE_CONTROL_END_NAMESPACE

#endif // HRUNTIMESERVICE_P_H
