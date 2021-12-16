#pragma once

#include "HElecCalibrateItemCollection.h"

HE_BEGIN_NAMESPACE

class IDataFactory;

class HElecCalibrateItemCollectionPrivate : public HCollectionPrivate<IElecCalibrateItem>
{
public:
    HElecCalibrateItemCollectionPrivate();

public:
    IDataFactory *factory = nullptr;
};

HE_END_NAMESPACE
