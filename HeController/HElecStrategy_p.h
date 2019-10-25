#ifndef HELECSTRATEGY_P_H
#define HELECSTRATEGY_P_H

#include "HElecStrategy.h"
#include "HAbstractActionStrategy_p.h"
#include "HeData/HDataGlobal.h"
#include "HeCommunicate/HCommunicateGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class ITestElec;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE
class IProtocol;
HE_COMMUNICATE_END_NAMESPACE
HE_COMMUNICATE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HElecStrategyPrivate : public HAbstractActionStrategyPrivate
{
public:
    HElecStrategyPrivate();

public:
    ITestElec *testElec;
    IProtocol *protocol;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HELECSTRATEGY_P_H
