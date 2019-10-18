/***************************************************************************************************
**      2019-10-15  IElecCalibrateCollection 电校准数据集合接口。
***************************************************************************************************/

#ifndef IELECCALIBRATECOLLECTION_H
#define IELECCALIBRATECOLLECTION_H

#include "HDataGlobal.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IElecCalibrate;
class IFileStream;

class IElecCalibrateCollection : public HCollection<IElecCalibrate>
{
public:
    using HCollection::HCollection;

public:
    // 获取文件流
    virtual IFileStream *fileStream() = 0;
};

HE_DATA_END_NAMESPACE

#endif // IELECCALIBRATECOLLECTION_H
