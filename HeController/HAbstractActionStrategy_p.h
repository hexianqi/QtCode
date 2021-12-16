#pragma once

#include "HAbstractActionStrategy.h"
#include <QtCore/QSet>

HE_BEGIN_NAMESPACE

class ITestData;

class HE_CONTROLLER_EXPORT HAbstractActionStrategyPrivate
{
public:
    HAbstractActionStrategyPrivate();

public:
    ITestData *testData;
    IProtocol *protocol = nullptr;
    QSet<HActionType> actionSupport;
};

HE_END_NAMESPACE
