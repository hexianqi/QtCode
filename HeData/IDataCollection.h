/***************************************************************************************************
**      2019-04-26  IDataCollection 数据集接口。
***************************************************************************************************/

#pragma once

#include "HeCore/HCollection.h"

HE_BEGIN_NAMESPACE

class IDataStream;
class IMultStream;

template <typename T>
class IDataCollection : public HCollection<T>
{
public:
    using HCollection<T>::HCollection;

public:
    // 获取数据流
    virtual IDataStream *dataStream() = 0;
    // 获取组合流
    virtual IMultStream *multStream() = 0;
    // 设置使用索引
    virtual void setUseIndex(QString value) = 0;
    // 使用的索引
    virtual QString useIndex() = 0;
    // 使用的项
    virtual T *useItem() = 0;
};

HE_END_NAMESPACE
