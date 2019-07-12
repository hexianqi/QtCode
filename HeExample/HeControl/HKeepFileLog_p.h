#ifndef HKEEPFILELOG_P_H
#define HKEEPFILELOG_P_H

#include "HKeepFileLog.h"
#include "HAbstractFileLog_p.h"

class QFile;

HE_CONTROL_BEGIN_NAMESPACE

class HKeepFileLogPrivate : public HAbstractFileLogPrivate
{
public:
    QFile *file;
    QString fileName;
};

HE_CONTROL_END_NAMESPACE

#endif // HKEEPFILELOG_P_H
