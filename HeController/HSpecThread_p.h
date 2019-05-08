#ifndef HSPECTHREAD_P_H
#define HSPECTHREAD_P_H

#include "HSpecThread.h"
#include "HAbstractThread_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HSpecThreadPrivate : public HAbstractThreadPrivate
{
public:
    HSpecThreadPrivate();

public:
    IProtocol *protocolSpec;
    ITestSpec *testSpec;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HSPECTHREAD_P_H
