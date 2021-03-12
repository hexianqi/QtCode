#pragma once

#include "HElecCalibrateItemCollection.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

class HElecCalibrateItemCollectionPrivate : public HCollectionPrivate<IElecCalibrateItem>
{
public:
    HElecCalibrateItemCollectionPrivate();

public:
    IDataFactory *factory = nullptr;
};

HE_DATA_END_NAMESPACE
