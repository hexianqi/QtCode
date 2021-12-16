/***************************************************************************************************
**      2019-04-26  IAdjustCollection 调整数据集合接口。
***************************************************************************************************/

#pragma once

#include "HDataCollection.h"

HE_BEGIN_NAMESPACE

class IAdjust;

class IAdjustCollection : public HDataCollection<IAdjust>
{
public:
    using HDataCollection::HDataCollection;

public:
    // 纠正
    virtual QVariantMap correct(QVariantMap value) = 0;
};

HE_END_NAMESPACE
