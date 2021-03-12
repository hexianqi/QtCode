#pragma once

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
    IDataStream *dataStream = nullptr;
};

HE_DATA_END_NAMESPACE
