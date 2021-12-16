/***************************************************************************************************
**      2019-05-05  IQualityCollection 品质数据集合接口。
***************************************************************************************************/

#pragma once

#include "HDataType.h"
#include "HDataCollection.h"

HE_BEGIN_NAMESPACE

class IQuality;

class IQualityCollection : public HDataCollection<IQuality>
{
public:
    using HDataCollection::HDataCollection;

public:
    // 检验
    virtual HQualityReport check(QVariantMap value, QVariantMap *color = nullptr) = 0;
    // 颜色
    virtual QColor color(HQualityReport type) = 0;
    // 偏差
    virtual double drift(QString type, QVariant value) = 0;
};

HE_END_NAMESPACE
