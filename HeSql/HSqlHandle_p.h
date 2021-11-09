#pragma once

#include "HSqlHandle.h"

HE_SQL_BEGIN_NAMESPACE

class HSqlHandlePrivate
{
public:
    ISqlTableModel *model = nullptr;
    QStringList fieldFind;
};

HE_SQL_END_NAMESPACE
