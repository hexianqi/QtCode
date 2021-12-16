#pragma once

#include "HChromatism.h"

HE_BEGIN_NAMESPACE

class IDataFactory;

class HChromatismPrivate : public HCollectionPrivate<IChromatismItem>
{
public:
    HChromatismPrivate();

public:
    IDataFactory *factory = nullptr;
    IChromatismItem *selectItem = nullptr;
};

HE_END_NAMESPACE
