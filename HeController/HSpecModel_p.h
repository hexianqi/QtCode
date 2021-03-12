#pragma once

#include "HSpecModel.h"
#include "HAbstractModel_p.h"

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HE_CONTROLLER_EXPORT HSpecModelPrivate : public HAbstractModelPrivate
{
public:
    HSpecModelPrivate();

public:
    ITestSpec *testSpec;
};

HE_CONTROLLER_END_NAMESPACE
