/***************************************************************************************************
**      2019-05-05  IQuality 品质数据接口。
***************************************************************************************************/

#pragma once

#include "HDataType.h"
#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class IQualityItemCollection;

class IQuality : public IInitializeable
{
public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;

public:
    // 品质数据子项集
    virtual IQualityItemCollection *itemCollection(HQualityType type) = 0;
    // 设置颜色
    virtual void setColor(HQualityReport type, const QColor &value) = 0;
    // 颜色
    virtual QColor color(HQualityReport type) = 0;
    // 检验
    virtual HQualityReport check(QVariantMap value, QVariantMap *color) = 0;
    // 偏差
    virtual double drift(QString type, QVariant value) = 0;
};

HE_END_NAMESPACE
