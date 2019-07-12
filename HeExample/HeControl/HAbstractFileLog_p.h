#ifndef HABSTRACTFILELOG_P_H
#define HABSTRACTFILELOG_P_H

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

#endif // HABSTRACTFILELOG_P_H
