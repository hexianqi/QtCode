#pragma once

#include "HRunTimeService.h"
#include "HeCore/HAbstractService_p.h"
#include <QtCore/QDateTime>

class QTimer;

HE_BEGIN_NAMESPACE

class HRunTimeServicePrivate : public HAbstractServicePrivate
{
public:
    ILogFile *file;
    QTimer *timer;
    int lastId;
    QDateTime startTime;
};

HE_END_NAMESPACE

