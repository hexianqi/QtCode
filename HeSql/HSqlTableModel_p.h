#pragma once

#include "HSqlTableModel.h"

HE_SQL_BEGIN_NAMESPACE

class HSqlTableModelPrivate
{
public:
    QStringList fields;
    int currentRow = -1;
};

HE_SQL_END_NAMESPACE
