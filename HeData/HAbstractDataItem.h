/***************************************************************************************************
**      2018-07-10  HAbstractDataItem 抽象数据子项。
***************************************************************************************************/

#pragma once

#include "IDataItem.h"

HE_DATA_BEGIN_NAMESPACE

class HAbstractDataItemPrivate;

class HAbstractDataItem : public virtual IDataItem
{
public:
    explicit HAbstractDataItem();
    ~HAbstractDataItem();

public:
    void initialize(QVariantMap param) override;

public:
    void setData(QString name, QVariant value) override;
    void setData(QVariantMap value) override;
    QVariant data(QString name) override;
    QVariantMap data() override;

protected:
    HAbstractDataItem(HAbstractDataItemPrivate &);

protected:
    QScopedPointer<HAbstractDataItemPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE
