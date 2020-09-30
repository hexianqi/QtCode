/***************************************************************************************************
**      2020-05-22  ILuminousCalibrateCollection 光校准数据集合接口。
***************************************************************************************************/

#pragma once

#include "HDataGlobal.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class ILuminousCalibrate;
class IDataStream;

class ILuminousCalibrateCollection : public HCollection<ILuminousCalibrate>
{
public:
    using HCollection::HCollection;

public:
    // 获取数据流
    virtual IDataStream *dataStream() = 0;
};

HE_DATA_END_NAMESPACE
