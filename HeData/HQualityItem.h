/***************************************************************************************************
**      2019-05-06  HQualityItem 品质数据项。
***************************************************************************************************/

#pragma once

#include "IQualityItem.h"
#include "HAbstractDataItem.h"

HE_BEGIN_NAMESPACE

class HQualityItemPrivate;

class HQualityItem : public HAbstractDataItem, public virtual IQualityItem
{
    Q_DECLARE_PRIVATE(HQualityItem)

public:
    explicit HQualityItem();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void restoreDefault() override;
    bool isContains(QVariant value, QColor *color) override;
    double drift(QVariant value) override;
    QStringList toStringList() override;

protected:
    HQualityItem(HQualityItemPrivate &);
};

HE_END_NAMESPACE
