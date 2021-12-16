#pragma once

#include "HLuminousCalibrateCollection.h"

HE_BEGIN_NAMESPACE

class IDataFactory;

class HLuminousCalibrateCollectionPrivate : public HCollectionPrivate<ILuminousCalibrate>
{
public:
    HLuminousCalibrateCollectionPrivate();

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);

public:
    IDataFactory *factory = nullptr;
    IDataStream *dataStream = nullptr;
};

HE_END_NAMESPACE
