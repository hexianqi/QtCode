#ifndef HBUILDER2000_P_H
#define HBUILDER2000_P_H

#include "HBuilder2000.h"
#include "HeGui/HAbstractBuilder_p.h"

HE_CONTROLLER_BEGIN_NAMESPACE
class ITestSpec;
HE_CONTROLLER_END_NAMESPACE

class HBuilder2000Private : public HAbstractBuilderPrivate
{
public:
    ITestSpec *testSpec = nullptr;
};

#endif // HBUILDER2000_P_H
