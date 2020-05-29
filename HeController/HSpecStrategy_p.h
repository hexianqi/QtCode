#ifndef HSPECSTRATEGY_P_H
#define HSPECSTRATEGY_P_H

#include "HSpecStrategy.h"
#include "HAbstractActionStrategy_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HSpecStrategyPrivate : public HAbstractActionStrategyPrivate
{
public:
    HSpecStrategyPrivate();

public:
    ITestSpec *testSpec;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HSPECSTRATEGY_P_H
