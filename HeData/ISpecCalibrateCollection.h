/***************************************************************************************************
**      2018-06-19  ISpecCalibrateCollection 光谱校准集合接口。
***************************************************************************************************/

#ifndef ISPECCALIBRATECOLLECTION_H
#define ISPECCALIBRATECOLLECTION_H

#include "HDataGlobal.h"
#include "HeCore/ICollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IFileStream;
class ISpecCalibrate;

class ISpecCalibrateCollection : virtual public ICollection<ISpecCalibrate>
{
public:
    virtual IFileStream *fileStream() = 0;
};

HE_DATA_END_NAMESPACE

#endif // ISPECCALIBRATECOLLECTION_H
