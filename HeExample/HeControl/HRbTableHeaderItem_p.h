#pragma once

#include "HRbTableHeaderItem.h"

HE_BEGIN_NAMESPACE

class HRbTableHeaderItemPrivate
{
public:
    HRbTableHeaderItemPrivate(HRbTableHeaderItem *);

public:
    int row = 0;
    int column = 0;
    HRbTableHeaderItem *parent = nullptr;
    QHash<QPair<int, int>, HRbTableHeaderItem *> childs;
    QHash<int, QVariant> datas;
};

HE_END_NAMESPACE
