#ifndef HSPECTHREAD_P_H
#define HSPECTHREAD_P_H

#include "HSpecThread.h"
#include "HAbstractThread_p.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class ITestSpec;

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
