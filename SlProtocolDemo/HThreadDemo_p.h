#ifndef HTHREADDEMO_P_H
#define HTHREADDEMO_P_H

#include "HThreadDemo.h"
#include "HeController/HAbstractThread_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

class HProtocolDemo;

class HThreadDemoPrivate : public HAbstractThreadPrivate
{
public:
    HThreadDemoPrivate();

public:
    HProtocolDemo *protocol;
    ITestSpec *testSpec;
};

#endif // HTHREADDEMO_P_H
