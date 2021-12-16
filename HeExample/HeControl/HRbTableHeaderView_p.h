#pragma once

#include "HRbTableHeaderView.h"

HE_BEGIN_NAMESPACE

class HRbTableHeaderModel;

class HRbTableHeaderViewPrivate
{
public:
    HRbTableHeaderViewPrivate(int rows, int columns);

public:
    HRbTableHeaderModel *model;
};

HE_END_NAMESPACE
