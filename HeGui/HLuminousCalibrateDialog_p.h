#pragma once

#include "HLuminousCalibrateDialog.h"

HE_BEGIN_NAMESPACE

class ITestData;
class IModel;
class ILuminousCalibrateCollection;
class HLuminousCalibrateItemWidget;

class HLuminousCalibrateDialogPrivate
{
public:
    HLuminousCalibrateDialogPrivate();

public:    
    ITestData *testData = nullptr;
    IModel *model = nullptr;
    ILuminousCalibrateCollection *calibrate = nullptr;
    HLuminousCalibrateItemWidget *currentWidget = nullptr;
    bool test = false;
    int module = -1;
    int index = -1;
    int gears = 0;
};

HE_END_NAMESPACE
