#pragma once

#include "HElecCalibrateDialog.h"
#include "HeController/HControllerGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IElecCalibrateCollection;
class ITestData;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HElecCalibrateDialogPrivate
{
public:
    HElecCalibrateDialogPrivate();

public:
    IElecCalibrateCollection *calibrate = nullptr;
    ITestData *testData = nullptr;
    IModel *model = nullptr;
    HElecCalibrateItemWidget *currentWidget = nullptr;
    bool loop = false;
    int module = -1;
    int index = -1;
};

HE_GUI_END_NAMESPACE
