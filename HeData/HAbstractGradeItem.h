/***************************************************************************************************
**      2019-04-17  HAbstractGradeItem 抽象分级数据子项。
***************************************************************************************************/

#ifndef HABSTRACTGRADEITEM_H
#define HABSTRACTGRADEITEM_H

#include "IGradeItem.h"

HE_DATA_BEGIN_NAMESPACE

class HAbstractGradeItemPrivate;

class HAbstractGradeItem : public IGradeItem
{
public:
    explicit HAbstractGradeItem();
    virtual ~HAbstractGradeItem();

public:
    void initialize(QVariantMap param) override;

public:
    void setData(QString name, QVariant value) override;
    void setData(QVariantMap value) override;
    QVariant data(QString name) override;

protected:
    HAbstractGradeItem(HAbstractGradeItemPrivate &);

protected:
    QScopedPointer<HAbstractGradeItemPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HABSTRACTGRADEITEM_H
