/***************************************************************************************************
**      2019-04-28  HAdjustItem 调整数据项。
***************************************************************************************************/

#pragma once

#include "IAdjustItem.h"
#include "HAbstractDataItem.h"

HE_DATA_BEGIN_NAMESPACE

class HAdjustItemPrivate;

class HAdjustItem : public HAbstractDataItem, public virtual IAdjustItem
{
    Q_DECLARE_PRIVATE(HAdjustItem)

public:
    explicit HAdjustItem();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void restoreDefault() override;
    QVariant correct(QVariant value) override;
    QStringList toStringList() override;

protected:
    HAdjustItem(HAdjustItemPrivate &);
};

HE_DATA_END_NAMESPACE
