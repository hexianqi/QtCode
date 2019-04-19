/***************************************************************************************************
**      2019-04-17  HAbstractGradeItem 抽象分级数据子项。
***************************************************************************************************/

#ifndef HABSTRACTGRADEITEM_H
#define HABSTRACTGRADEITEM_H

#include "IGradeItem.h"
#include "HAbstractDataItem.h"

HE_DATA_BEGIN_NAMESPACE

class HAbstractGradeItemPrivate;

class HAbstractGradeItem : public HAbstractDataItem, public IGradeItem
{
    Q_DECLARE_PRIVATE(HAbstractGradeItem)

public:
    explicit HAbstractGradeItem();
    ~HAbstractGradeItem() override;

protected:
    HAbstractGradeItem(HAbstractGradeItemPrivate &);
};

HE_DATA_END_NAMESPACE

#endif // HABSTRACTGRADEITEM_H
