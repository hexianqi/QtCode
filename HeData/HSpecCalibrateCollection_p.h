#pragma once

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
    IDataStream *dataStream = nullptr;
};

HE_DATA_END_NAMESPACE
