#pragma once

#include "HAdjust2.h"

HE_BEGIN_NAMESPACE

class IDataFactory;

class HAdjust2Private : public HCollectionPrivate<IAdjustItemCollection>
{
public:
    HAdjust2Private();

public:
    IDataFactory *factory = nullptr;
    IAdjustItemCollection *selectItem = nullptr;
};

HE_END_NAMESPACE

