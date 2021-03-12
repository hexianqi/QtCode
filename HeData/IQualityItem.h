/***************************************************************************************************
**      2019-05-05  IQualityItem 品质数据项接口。
***************************************************************************************************/

#pragma once

#include "HAbstractDataItem.h"

HE_DATA_BEGIN_NAMESPACE

class IQualityItem : public HAbstractDataItem
{
public:
    using HAbstractDataItem::HAbstractDataItem;

public:
    // 还原默认
    virtual void restoreDefault() = 0;
    // 是否在范围内
    virtual bool isContains(QVariant value, QColor *color) = 0;
    // 偏差
    virtual double drift(QVariant value) = 0;
    // 获取数据
    virtual QStringList toStringList() = 0;
};

HE_DATA_END_NAMESPACE
