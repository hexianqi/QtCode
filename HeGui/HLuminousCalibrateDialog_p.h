#pragma once

#include "HLuminousCalibrateDialog.h"
#include "HeController/HControllerGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class ILuminousCalibrateCollection;
class ITestData;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HLuminousCalibrateItemWidget;

class HLuminousCalibrateDialogPrivate
{
public:
    HLuminousCalibrateDialogPrivate();

public:
    ILuminousCalibrateCollection *calibrate = nullptr;
    ITestData *testData = nullptr;
    IModel *model = nullptr;
    HLuminousCalibrateItemWidget *currentWidget = nullptr;
    bool test = false;
    int module = -1;
    int index = -1;
    int gears = 0;
};

HE_GUI_END_NAMESPACE
