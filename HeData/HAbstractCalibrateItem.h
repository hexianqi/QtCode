/***************************************************************************************************
**      2018-07-10  HAbstractCalibrateItem 抽象校准子项。
***************************************************************************************************/

#ifndef HABSTRACTCALIBRATEITEM_H
#define HABSTRACTCALIBRATEITEM_H

#include "ICalibrateItem.h"

HE_DATA_BEGIN_NAMESPACE

class HAbstractCalibrateItemPrivate;

class HAbstractCalibrateItem : public ICalibrateItem
{
public:
    explicit HAbstractCalibrateItem();
    virtual ~HAbstractCalibrateItem();

public:
    void initialize(QVariantMap param) override;
    void setData(QString name, QVariant value) override;
    QVariant data(QString name) override;

protected:
    HAbstractCalibrateItem(HAbstractCalibrateItemPrivate &);

protected:
    QScopedPointer<HAbstractCalibrateItemPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HABSTRACTCALIBRATEITEM_H
