#pragma once

#include "HKeepFileLog.h"
#include "HAbstractFileLog_p.h"

class QFile;

HE_BEGIN_NAMESPACE

class HKeepFileLogPrivate : public HAbstractFileLogPrivate
{
public:
    QFile *file;
    QString fileName;
};

HE_END_NAMESPACE
