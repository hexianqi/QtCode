/***************************************************************************************************
**      2019-05-17  IChromatism 色容差数据接口。
***************************************************************************************************/

#pragma once

#include "HeCore/HCollection.h"

HE_BEGIN_NAMESPACE

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
    // 色容差详情
    virtual QVariantMap detail() = 0;
};

HE_END_NAMESPACE
