#pragma once

#include "HModelDemo.h"
#include "HeController/HAbstractModel_p.h"

class HTestWidgetDemo;

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
HE_DATA_END_NAMESPACE

class HModelDemoPrivate : public HAbstractModelPrivate
{
public:
    HModelDemoPrivate(IModel *);

public:
    HTestWidgetDemo *widget();

public:
    ITestSpec *testSpec = nullptr;
    HTestWidgetDemo *testWidget = nullptr;
};
