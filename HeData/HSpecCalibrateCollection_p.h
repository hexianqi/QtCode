#ifndef HSPECCALIBRATECOLLECTION_P_H
#define HSPECCALIBRATECOLLECTION_P_H

#include "HSpecCalibrateCollection.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

class HSpecCalibrateCollectionPrivate : public HCollectionPrivate<ISpecCalibrate>
{
public:
    HSpecCalibrateCollectionPrivate();

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);

public:
    IDataFactory *factory = nullptr;
    IFileStream *fileStream = nullptr;
};

HE_DATA_END_NAMESPACE

#endif // HSPECCALIBRATECOLLECTION_P_H
