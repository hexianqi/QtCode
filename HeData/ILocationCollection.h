/***************************************************************************************************
**      2022-01-26  ILocationCollection 定位数据集合接口。
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
    // 边框
    virtual QRect boundingRect() = 0;
    // 形状
    virtual QPolygon polygon() = 0;
};

HE_END_NAMESPACE
