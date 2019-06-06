#ifndef HRBTABLEHEADERMODEL_P_H
#define HRBTABLEHEADERMODEL_P_H

#include "HRbTableHeaderModel.h"

HE_CONTROL_BEGIN_NAMESPACE

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

HE_CONTROL_END_NAMESPACE

#endif // HRBTABLEHEADERMODEL_P_H
