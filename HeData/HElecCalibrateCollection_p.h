#ifndef HELECCALIBRATECOLLECTION_P_H
#define HELECCALIBRATECOLLECTION_P_H

#include "HElecCalibrateCollection.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

class HElecCalibrateCollectionPrivate : public HCollectionPrivate<IElecCalibrate>
{
public:
    HElecCalibrateCollectionPrivate();

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);

public:
    IDataFactory *factory = nullptr;
    IFileStream *fileStream = nullptr;
};

HE_DATA_END_NAMESPACE

#endif // HELECCALIBRATECOLLECTION_P_H
