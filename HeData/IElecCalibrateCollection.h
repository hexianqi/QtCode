/***************************************************************************************************
**      2019-10-15  IElecCalibrateCollection 电校准数据集合接口。
***************************************************************************************************/

#pragma once

#include "HDataGlobal.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IElecCalibrate;
class IDataStream;

class IElecCalibrateCollection : public HCollection<IElecCalibrate>
{
public:
    using HCollection::HCollection;

public:
    // 获取数据流
    virtual IDataStream *dataStream() = 0;
};

HE_DATA_END_NAMESPACE
