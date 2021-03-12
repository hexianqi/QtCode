#pragma once

#include "HQualityItemCollection.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

class HQualityItemCollectionPrivate : public HCollectionPrivate<IQualityItem>
{
public:
    HQualityItemCollectionPrivate();

public:
    IDataFactory *factory = nullptr;
};

HE_DATA_END_NAMESPACE
