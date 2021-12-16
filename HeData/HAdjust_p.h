#pragma once

#include "HAdjust.h"

HE_BEGIN_NAMESPACE

class IDataFactory;

class HAdjustPrivate : public HCollectionPrivate<IAdjustItem>
{
public:
    HAdjustPrivate();

public:
    IDataFactory *factory = nullptr;
};

HE_END_NAMESPACE
