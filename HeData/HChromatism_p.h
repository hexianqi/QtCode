#pragma once

#include "HChromatism.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

class HChromatismPrivate : public HCollectionPrivate<IChromatismItem>
{
public:
    HChromatismPrivate();

public:
    IDataFactory *factory = nullptr;
    IChromatismItem *selectItem = nullptr;
};

HE_DATA_END_NAMESPACE
