#pragma once

#include "HBorderLayout.h"

HE_BEGIN_NAMESPACE

class HBorderLayoutPrivate
{
public:
    QList<QPair<QLayoutItem *, HBorderLayout::Position>> items;
};

HE_END_NAMESPACE
