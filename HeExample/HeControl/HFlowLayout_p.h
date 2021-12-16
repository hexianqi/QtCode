#pragma once

#include "HFlowLayout.h"

HE_BEGIN_NAMESPACE

class HFlowLayoutPrivate
{
public:
    HFlowLayoutPrivate(int hSpace = -1, int vSpacing = -1);

public:
    QList<QLayoutItem *> items;
    int hSpacing;
    int vSpacing;
};

HE_END_NAMESPACE
