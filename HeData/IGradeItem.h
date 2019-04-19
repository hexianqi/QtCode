/***************************************************************************************************
**      2019-04-17  IGradeItem  分级数据子项接口。
***************************************************************************************************/

#ifndef IGRADEITEM_H
#define IGRADEITEM_H

#include "IDataItem.h"

HE_DATA_BEGIN_NAMESPACE

class IGradeItem : virtual public IDataItem
{
public:
    // 索引
    virtual QSet<int> indexOf(QVariant value) = 0;
    // 总数
    virtual int count() = 0;
};

HE_DATA_END_NAMESPACE

#endif // IGRADEITEM_H
