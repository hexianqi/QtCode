/***************************************************************************************************
**      2019-04-17  IGradeItem  分级数据项接口。
***************************************************************************************************/

#pragma once

#include "IDataItem.h"

HE_BEGIN_NAMESPACE

class IGradeItem : public virtual IDataItem
{
public:
    // 设置分级
    virtual void setLevels(QVariant value) = 0;
    // 获取所有分级
    virtual QVariant levels() = 0;
    // 获取索引
    virtual QSet<int> indexOf(QVariant value) = 0;
    // 获取总数
    virtual int count() = 0;
    // 获取表头
    virtual QStringList headers() = 0;
    // 获取数据类型
    virtual QStringList types() = 0;
    // 获取分级
    virtual QStringList level(int i) = 0;
};

HE_END_NAMESPACE
