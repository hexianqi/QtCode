#ifndef HRBTABLEHEADERITEM_P_H
#define HRBTABLEHEADERITEM_P_H

#include "HRbTableHeaderItem.h"

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

#endif // HRBTABLEHEADERITEM_P_H
