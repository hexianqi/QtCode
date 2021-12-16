#pragma once

#include "HRbTableHeaderModel.h"

HE_BEGIN_NAMESPACE

class HRbTableHeaderItem;

class HRbTableHeaderModelPrivate
{
public:
    HRbTableHeaderModelPrivate(int rows, int columns);
    ~HRbTableHeaderModelPrivate();

public:
    int rowCount = 0;
    int columnCount = 0;
    HRbTableHeaderItem *root;
};

HE_END_NAMESPACE
