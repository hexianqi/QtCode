#pragma once

#include "HQualityItemCollection.h"

HE_BEGIN_NAMESPACE

class IDataFactory;

class HQualityItemCollectionPrivate : public HCollectionPrivate<IQualityItem>
{
public:
    HQualityItemCollectionPrivate();

public:
    IDataFactory *factory = nullptr;
};

HE_END_NAMESPACE
