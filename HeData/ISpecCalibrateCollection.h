/***************************************************************************************************
**      2018-06-19  ISpecCalibrateCollection 光谱校准数据集合接口。
***************************************************************************************************/

#ifndef ISPECCALIBRATECOLLECTION_H
#define ISPECCALIBRATECOLLECTION_H

#include "HDataGlobal.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

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

HE_DATA_END_NAMESPACE

#endif // ISPECCALIBRATECOLLECTION_H
