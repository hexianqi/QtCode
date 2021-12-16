#pragma once

#include "HRegister.h"
#include <QtCore/QString>

HE_BEGIN_NAMESPACE

class HRegisterPrivate
{
public:
    QString registerId();
    QString registerCode();
    bool isExpires();
    void trial();

public:
    bool setRegisterCode(const QString &value);

public:
    QString id;
    QString serialNumber;
    int trialTimes;
    int firstDate;
};

HE_END_NAMESPACE
