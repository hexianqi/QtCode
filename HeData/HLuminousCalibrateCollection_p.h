#pragma once

#include "HLuminousCalibrateCollection.h"

HE_DATA_BEGIN_NAMESPACE

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
    IFileStream *fileStream = nullptr;
};

HE_DATA_END_NAMESPACE
