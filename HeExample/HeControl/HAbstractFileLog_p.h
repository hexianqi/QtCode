#pragma once

#include "HAbstractFileLog.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractFileLogPrivate
{
public:
    HAbstractFileLogPrivate();

public:
    QString path;
    QString name;
    QString dataFormat;
};

HE_CONTROL_END_NAMESPACE
