#ifndef HMODELSPEC_P_H
#define HMODELSPEC_P_H

#include "HModelSpec.h"
#include "HeController/HAbstractModel_p.h"

HE_CONTROLLER_BEGIN_NAMESPACE
class ITestSpec;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

class HModelSpecPrivate : public HAbstractModelPrivate
{
public:
    HModelSpecPrivate(HModelSpec *);

public:
    ITestSpec *testSpec;
};

#endif // HMODELSPEC_P_H
