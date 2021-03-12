/***************************************************************************************************
**      2019-05-20  IChromatismCollection 色容差数据集合接口。
***************************************************************************************************/

#pragma once

#include "HDataCollection.h"

HE_DATA_BEGIN_NAMESPACE

class IChromatism;

class IChromatismCollection : public HDataCollection<IChromatism>
{
public:
    using HDataCollection::HDataCollection;

public:
    // 计算色容差
    virtual double calcSdcm(double tc, QPointF xy) = 0;
    // 使用数据
    virtual QVariantMap toMap() = 0;
};

HE_DATA_END_NAMESPACE
