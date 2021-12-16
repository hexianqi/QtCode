#pragma once

#include "HSpecModel.h"
#include "HAbstractModel_p.h"

HE_BEGIN_NAMESPACE

class ITestSpec;

class HE_CONTROLLER_EXPORT HSpecModelPrivate : public HAbstractModelPrivate
{
public:
    HSpecModelPrivate();

public:
    ITestSpec *testSpec;
};

HE_END_NAMESPACE
