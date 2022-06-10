#pragma once

#include "HFlowLayout.h"

HE_BEGIN_NAMESPACE

class HFlowLayoutPrivate
{
public:
    HFlowLayoutPrivate(int horizontalSpacing = -1, int verticalSpacing = -1);

public:
    QList<QLayoutItem *> items;
    int horizontalSpacing;
    int verticalSpacing;
};

HE_END_NAMESPACE
