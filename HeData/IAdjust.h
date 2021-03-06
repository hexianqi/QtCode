/***************************************************************************************************
**      2019-04-26  IAdjust 调整数据接口。
***************************************************************************************************/

#ifndef IADJUST_H
#define IADJUST_H

#include "HDataGlobal.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IAdjustItem;
class IDataFactory;

class IAdjust : public HCollection<IAdjustItem>
{
public:
    using HCollection::HCollection;

public:
    // 读取内容
    virtual void readContent(QDataStream &, IDataFactory *) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;

public:
    // 还原默认
    virtual void restoreDefault() = 0;
    // 纠正
    virtual QVariantMap correct(QVariantMap value) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IADJUST_H
