/***************************************************************************************************
**      2018-07-10  HAbstractDataItem 抽象数据子项。
***************************************************************************************************/

#ifndef HABSTRACTDATAITEM_H
#define HABSTRACTDATAITEM_H

#include "IDataItem.h"

HE_DATA_BEGIN_NAMESPACE

class HAbstractDataItemPrivate;

class HAbstractDataItem : virtual public IDataItem
{
public:
    explicit HAbstractDataItem();
    virtual ~HAbstractDataItem();

public:
    void initialize(QVariantMap param) override;

public:
    void setData(QString name, QVariant value) override;
    QVariant data(QString name) override;

protected:
    HAbstractDataItem(HAbstractDataItemPrivate &);

protected:
    QScopedPointer<HAbstractDataItemPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HABSTRACTDATAITEM_H
