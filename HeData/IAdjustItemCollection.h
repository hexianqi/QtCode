/***************************************************************************************************
**      2021-03-09  IAdjustItemCollection 调整项集合接口
***************************************************************************************************/

#pragma once

#include "HDataGlobal.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IAdjustItem;

class IAdjustItemCollection : public HCollection<IAdjustItem>
{
public:
    using HCollection::HCollection;

public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;

public:
    // 设置数据
    virtual void setData(QString name, QVariant value) = 0;
    // 获取数据
    virtual QVariant data(QString name) = 0;

public:
    // 还原默认
    virtual void restoreDefault() = 0;
    // 纠正
    virtual QVariantMap correct(QVariantMap value) = 0;
};

HE_DATA_END_NAMESPACE
