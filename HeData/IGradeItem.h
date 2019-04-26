/***************************************************************************************************
**      2019-04-17  IGradeItem  分级数据子项接口。
***************************************************************************************************/

#ifndef IGRADEITEM_H
#define IGRADEITEM_H

#include "IDataItem.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IGradeItem : public IDataItem
{
public:
    // 设置分级
    virtual void setLevels(QVariant value) = 0;
    // 获取所有分级
    virtual QVariant levels() = 0;
    // 获取分级
    virtual QStringList level(int i) = 0;
    // 获取索引
    virtual QSet<int> indexOf(QVariant value) = 0;
    // 获取总数
    virtual int count() = 0;
    // 获取表头
    virtual QStringList headers() = 0;
    // 获取数据类型
    virtual QStringList types() = 0;
};

HE_DATA_END_NAMESPACE

#endif // IGRADEITEM_H
