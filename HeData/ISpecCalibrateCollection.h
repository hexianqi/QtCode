/***************************************************************************************************
**      2018-06-19  ISpecCalibrateCollection 光谱校准数据集合接口。
***************************************************************************************************/

#pragma once

#include "HeCore/HCollection.h"

HE_BEGIN_NAMESPACE

class ISpecCalibrate;
class IDataStream;

class ISpecCalibrateCollection : public HCollection<ISpecCalibrate>
{
public:
    using HCollection::HCollection;

public:
    // 获取数据流
    virtual IDataStream *dataStream() = 0;
};

HE_END_NAMESPACE
