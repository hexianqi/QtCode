#pragma once

#include "HSqlHandle.h"

HE_BEGIN_NAMESPACE

class HSqlHandlePrivate
{
public:
    ISqlTableModel *model = nullptr;
    QStringList fieldFind;
};

HE_END_NAMESPACE
