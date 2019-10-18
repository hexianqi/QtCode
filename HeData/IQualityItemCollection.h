/***************************************************************************************************
**      2019-05-05  IQualityItemCollection 品质数据项集合接口。
***************************************************************************************************/

#ifndef IQUALITYITEMCOLLECTION_H
#define IQUALITYITEMCOLLECTION_H

#include "HDataGlobal.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IQualityItem;

class IQualityItemCollection : public HCollection<IQualityItem>
{
public:
    using HCollection::HCollection;

public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;

public:
    // 检验（-1：数据错误；0：在范围外；1：在范围内）
    virtual int check(QVariantMap value, QVariantMap *color) = 0;
    // 偏差
    virtual double drift(QString type, QVariant value) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IQUALITYITEMCOLLECTION_H
