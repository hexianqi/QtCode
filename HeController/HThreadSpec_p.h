#ifndef HTHREADSPEC_P_H
#define HTHREADSPEC_P_H

#include "HThreadSpec.h"
#include "HAbstractThread_p.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class ITestSpec;

class HThreadSpecPrivate : public HAbstractThreadPrivate
{
    Q_DECLARE_PUBLIC(HThreadSpec)

public:
    HThreadSpecPrivate(HThreadSpec *q);

public:
    IProtocol *protocolSpec;
    ITestSpec *testSpec;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HTHREADSPEC_P_H
