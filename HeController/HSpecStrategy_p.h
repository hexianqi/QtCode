#pragma once

#include "HSpecStrategy.h"
#include "HAbstractActionStrategy_p.h"

HE_BEGIN_NAMESPACE

class ITestSpec;

class HSpecStrategyPrivate : public HAbstractActionStrategyPrivate
{
public:
    HSpecStrategyPrivate();

public:
    ITestSpec *testSpec;
};

HE_END_NAMESPACE
