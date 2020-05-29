#pragma once

#include "HLuminousCalibrate.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

class HLuminousCalibratePrivate : public HCollectionPrivate<ILuminousCalibrateItem>
{
public:
    HLuminousCalibratePrivate();

public:
    IDataFactory *factory = nullptr;
};

HE_DATA_END_NAMESPACE

