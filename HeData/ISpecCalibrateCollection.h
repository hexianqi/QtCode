#ifndef ISPECCALIBRATECOLLECTION_H
#define ISPECCALIBRATECOLLECTION_H

#include "IFileStream.h"
#include "HeCore/ICollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class ISpecCalibrate;

class ISpecCalibrateCollection : virtual public ICollection<ISpecCalibrate>, virtual public IFileStream
{

};

HE_DATA_END_NAMESPACE

#endif // ISPECCALIBRATECOLLECTION_H
