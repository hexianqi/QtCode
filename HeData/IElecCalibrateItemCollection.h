/***************************************************************************************************
**      2019-10-16 IElecCalibrateItemCollection 电参数校准数据项集合。
***************************************************************************************************/

#pragma once

#include "HDataGlobal.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IElecCalibrateItem;

class IElecCalibrateItemCollection : public HCollection<IElecCalibrateItem>
{
public:
    using HCollection::HCollection;

public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;
};

HE_DATA_END_NAMESPACE
