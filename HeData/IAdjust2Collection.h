/***************************************************************************************************
**      2021-03-09  IAdjust2Collection 调整数据集合接口。
***************************************************************************************************/

#pragma once

#include "HDataCollection.h"

HE_BEGIN_NAMESPACE

class IAdjust2;

class IAdjust2Collection : public HDataCollection<IAdjust2>
{
public:
    using HDataCollection::HDataCollection;

public:
    // 纠正
    virtual QVariantMap correct(double tc, QVariantMap value) = 0;
};

HE_END_NAMESPACE
