#pragma once

#include "HRbTableHeaderModel.h"

class HRbTableHeaderItem;

class QDESIGNER_WIDGET_EXPORT HRbTableHeaderModelPrivate
{
public:
    HRbTableHeaderModelPrivate(int rows, int columns);
    ~HRbTableHeaderModelPrivate();

public:
    int rowCount = 0;
    int columnCount = 0;
    HRbTableHeaderItem *root;
};
