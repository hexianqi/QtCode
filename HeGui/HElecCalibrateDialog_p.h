#pragma once

#include "HElecCalibrateDialog.h"

HE_BEGIN_NAMESPACE

class IElecCalibrateCollection;
class ITestData;
class IModel;

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

HE_END_NAMESPACE
