#pragma once

#include "HRbTableHeaderItem.h"

class QDESIGNER_WIDGET_EXPORT HRbTableHeaderItemPrivate
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
