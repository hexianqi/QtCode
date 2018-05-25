#ifndef HSPECCALIBRATECOLLECTION_P_H
#define HSPECCALIBRATECOLLECTION_P_H

#include "HSpecCalibrateCollection.h"
#include "HAbstractFileStream_p.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

class HSpecCalibrateCollectionPrivate : public HAbstractFileStreamPrivate
{
public:
    HSpecCalibrateCollectionPrivate(IDataFactory *);
};


HE_DATA_END_NAMESPACE

#endif // HSPECCALIBRATECOLLECTION_P_H
