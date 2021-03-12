#pragma once

#include "HRbTableHeaderView.h"

HE_CONTROL_BEGIN_NAMESPACE

class HRbTableHeaderModel;

class HRbTableHeaderViewPrivate
{
public:
    HRbTableHeaderViewPrivate(int rows, int columns);

public:
    HRbTableHeaderModel *model;
};

HE_CONTROL_END_NAMESPACE
