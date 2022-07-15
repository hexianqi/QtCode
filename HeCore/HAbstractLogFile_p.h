#pragma once

#include "HAbstractLogFile.h"

HE_BEGIN_NAMESPACE

class HAbstractLogFilePrivate
{
public:
    HAbstractLogFilePrivate();

public:
    QString path;
    QString name;
    QString format;
};

HE_END_NAMESPACE

