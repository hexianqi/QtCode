#pragma once

#include "HNamespace.h"
#include "HControllerGlobal.h"

HE_BEGIN_NAMESPACE

class IProtocol;
class ITestData;

class HE_CONTROLLER_EXPORT HControllerHelper
{
public:
    static void multGetSpectrum(IProtocol *, ITestData *, int times = 1);
};

HE_END_NAMESPACE

