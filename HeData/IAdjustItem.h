/***************************************************************************************************
**      2019-04-26  IGradeItem 调整数据项接口。
***************************************************************************************************/

#ifndef IADJUSTITEM_H
#define IADJUSTITEM_H

#include "IDataItem.h"

HE_DATA_BEGIN_NAMESPACE

class IAdjustItem : public IDataItem
{
public:
    // 还原默认
    virtual void restoreDefault() = 0;
    // 纠正
    virtual QVariant correct(QVariant value) = 0;
    // 获取数据
    virtual QStringList toStringList() = 0;
};

HE_DATA_END_NAMESPACE

#endif // IADJUSTITEM_H
