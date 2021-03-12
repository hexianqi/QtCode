#pragma once

#include "HAbstractActionStrategy.h"
#include "HeData/HDataGlobal.h"
#include <QtCore/QSet>

HE_DATA_BEGIN_NAMESPACE
class ITestData;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HE_CONTROLLER_EXPORT HAbstractActionStrategyPrivate
{
public:
    HAbstractActionStrategyPrivate();

public:
    ITestData *testData;
    IProtocol *protocol = nullptr;
    QSet<HActionType> actionSupport;
};

HE_CONTROLLER_END_NAMESPACE
