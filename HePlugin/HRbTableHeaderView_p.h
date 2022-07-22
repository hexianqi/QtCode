#pragma once

#include "HRbTableHeaderView.h"

class HRbTableHeaderModel;

class QDESIGNER_WIDGET_EXPORT HRbTableHeaderViewPrivate
{
public:
    HRbTableHeaderViewPrivate(int rows, int columns);

public:
    HRbTableHeaderModel *model;
};

