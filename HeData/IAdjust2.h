/***************************************************************************************************
**      2021-03-09  IAdjust2 调整数据接口。
***************************************************************************************************/

#pragma once

#include "HDataGlobal.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IAdjustItemCollection;

class IAdjust2 : public HCollection<IAdjustItemCollection>
{
public:
    using HCollection::HCollection;

public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;

public:
    // 还原默认
    virtual void restoreDefault() = 0;
    // 纠正
    virtual QVariantMap correct(double tc, QVariantMap value) = 0;
};

HE_DATA_END_NAMESPACE
