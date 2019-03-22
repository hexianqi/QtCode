#ifndef HSPECCALIBRATECOLLECTION_P_H
#define HSPECCALIBRATECOLLECTION_P_H

#include "HSpecCalibrateCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecCalibrateCollectionPrivate
{
public:
    HSpecCalibrateCollectionPrivate(HSpecCalibrateCollection *, IDataFactory *);

public:
    HSpecCalibrateCollection *q_ptr;
    IDataFactory *factory;
    IFileStream *fileStream;
};

HE_DATA_END_NAMESPACE

#endif // HSPECCALIBRATECOLLECTION_P_H
