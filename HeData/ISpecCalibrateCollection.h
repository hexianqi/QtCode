/***************************************************************************************************
**      2018-06-19  ISpecCalibrateCollection 光谱校准数据集合接口。
***************************************************************************************************/

#ifndef ISPECCALIBRATECOLLECTION_H
#define ISPECCALIBRATECOLLECTION_H

#include "HDataGlobal.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IFileStream;
class ISpecCalibrate;

class ISpecCalibrateCollection : public HCollection<ISpecCalibrate>
{
public:
    using HCollection::HCollection;

public:
    // 获取文件流
    virtual IFileStream *fileStream() = 0;
};

HE_DATA_END_NAMESPACE

#endif // ISPECCALIBRATECOLLECTION_H
