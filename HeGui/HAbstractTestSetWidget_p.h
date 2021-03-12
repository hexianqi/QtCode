#pragma once

#include "HAbstractTestSetWidget.h"
#include "HeController/HControllerGlobal.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class ITestData;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HE_GUI_EXPORT HAbstractTestSetWidgetPrivate
{
public:
    HAbstractTestSetWidgetPrivate();

public:
    IModel *model;
    ITestData *testData;
    bool testState = false;
    int testMode = 0;
    int saveMode = 0;
};

HE_GUI_END_NAMESPACE
