#pragma once

#include "HBorderLayout.h"

HE_CONTROL_BEGIN_NAMESPACE

class HBorderLayoutPrivate
{
public:
    QList<QPair<QLayoutItem *, HBorderLayout::Position>> items;
};

HE_CONTROL_END_NAMESPACE
