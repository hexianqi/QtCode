#pragma once

#include "HLuminousCalibrateDialog.h"

HE_BEGIN_NAMESPACE

class ILuminousCalibrateCollection;
class ITestData;
class IModel;
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

HE_END_NAMESPACE
