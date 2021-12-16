#pragma once

#include "HLuminousCalibrateItem.h"
#include "HAbstractDataItem_p.h"

HE_BEGIN_NAMESPACE

class HLuminousCalibrateItemPrivate : public HAbstractDataItemPrivate
{
public:
    HLuminousCalibrateItemPrivate();

public:
    QList<QPolygonF> relations;
};

HE_END_NAMESPACE

