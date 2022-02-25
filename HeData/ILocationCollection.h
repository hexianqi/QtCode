/***************************************************************************************************
**      2022-01-26  ILocationCollection 布局数据集合接口。
***************************************************************************************************/

#pragma once

#include "HDataCollection.h"

HE_BEGIN_NAMESPACE

class ILocation;

class ILocationCollection : public HDataCollection<ILocation>
{
public:
    using HDataCollection::HDataCollection;

public:
    // 形状
    virtual QPolygon polygon() = 0;
};

HE_END_NAMESPACE
