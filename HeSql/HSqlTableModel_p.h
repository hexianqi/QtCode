#pragma once

#include "HSqlTableModel.h"

HE_BEGIN_NAMESPACE

class HSqlTableModelPrivate
{
public:
    QStringList fields;
    int currentRow = -1;
};

HE_END_NAMESPACE
