#ifndef HSPECCALIBRATECOLLECTION_P_H
#define HSPECCALIBRATECOLLECTION_P_H

#include "HSpecCalibrateCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecCalibrateCollectionPrivate
{
    Q_DECLARE_PUBLIC(HSpecCalibrateCollection)

public:
    HSpecCalibrateCollectionPrivate(HSpecCalibrateCollection *q, IDataFactory *f);

public:
    HSpecCalibrateCollection *q_ptr;
    IDataFactory *factory;
    IFileStream *fileStream;
};

HE_DATA_END_NAMESPACE

#endif // HSPECCALIBRATECOLLECTION_P_H
