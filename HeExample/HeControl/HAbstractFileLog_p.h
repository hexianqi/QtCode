#pragma once

#include "HAbstractFileLog.h"

HE_BEGIN_NAMESPACE

class HAbstractFileLogPrivate
{
public:
    HAbstractFileLogPrivate();

public:
    QString path;
    QString name;
    QString dataFormat;
};

HE_END_NAMESPACE
