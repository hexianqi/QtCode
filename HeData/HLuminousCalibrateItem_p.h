#pragma once

#include "HLuminousCalibrateItem.h"
#include "HAbstractDataItem_p.h"

HE_DATA_BEGIN_NAMESPACE

class HLuminousCalibrateItemPrivate : public HAbstractDataItemPrivate
{
public:
    HLuminousCalibrateItemPrivate();

public:
    QList<QPolygonF> relations;
};

HE_DATA_END_NAMESPACE

