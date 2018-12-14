#ifndef HBORDERLAYOUT_P_H
#define HBORDERLAYOUT_P_H

#include "HBorderLayout.h"

HE_EXAMPLE_BEGIN_NAMESPACE

class HBorderLayoutPrivate
{
public:
    QList<QPair<QLayoutItem *, HBorderLayout::Position>> items;
};

HE_EXAMPLE_END_NAMESPACE

#endif // HBORDERLAYOUT_P_H
