#ifndef HRBTABLEHEADERVIEW_P_H
#define HRBTABLEHEADERVIEW_P_H

#include "HRbTableHeaderView.h"

class HRbTableHeaderModel;

class HRbTableHeaderViewPrivate
{
public:
    HRbTableHeaderViewPrivate(int rows, int columns);

public:
    HRbTableHeaderModel *model;
};

#endif // HRBTABLEHEADERVIEW_P_H
