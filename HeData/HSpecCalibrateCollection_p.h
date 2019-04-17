#ifndef HSPECCALIBRATECOLLECTION_P_H
#define HSPECCALIBRATECOLLECTION_P_H

#include "HSpecCalibrateCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecCalibrateCollectionPrivate : public HCollectionPrivate<ISpecCalibrate>
{
public:
    HSpecCalibrateCollectionPrivate(IDataFactory *);

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);

public:
    IDataFactory *factory;
    IFileStream *fileStream;
};

HE_DATA_END_NAMESPACE

#endif // HSPECCALIBRATECOLLECTION_P_H
