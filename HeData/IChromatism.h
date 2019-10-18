/***************************************************************************************************
**      2019-05-17  IChromatism 色容差数据接口。
***************************************************************************************************/

#ifndef ICHROMATISM_H
#define ICHROMATISM_H

#include "HDataGlobal.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IChromatismItem;

class IChromatism : public HCollection<IChromatismItem>
{
public:
    using HCollection::HCollection;

public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;

public:
    // 计算色容差
    virtual double calcSdcm(double tc, QPointF xy) = 0;
    // 转成Json
    virtual QJsonObject toJson() = 0;
};

HE_DATA_END_NAMESPACE

#endif // ICHROMATISM_H
