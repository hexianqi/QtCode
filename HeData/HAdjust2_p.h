#pragma once

#include "HAdjust2.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

class HAdjust2Private : public HCollectionPrivate<IAdjustItemCollection>
{
public:
    HAdjust2Private();

public:
    IDataFactory *factory = nullptr;
    IAdjustItemCollection *selectItem = nullptr;
};

HE_DATA_END_NAMESPACE

