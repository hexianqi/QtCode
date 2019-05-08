#ifndef HADJUSTEDITDIALOG_P_H
#define HADJUSTEDITDIALOG_P_H

#include "HAdjustEditDialog.h"
#include "HeController/HControllerGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class ITestData;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecEnergyWidget;
class HAdjustEditWidget;

class HAdjustEditDialogPrivate
{
public:
    HAdjustEditDialogPrivate();

public:
    IModel *model;
    ITestData *testData;

public:
    HAdjustEditWidget *editWidget;
    HSpecEnergyWidget *energyWidget;
    ITestSetWidget *testSetWidget;
};

HE_GUI_END_NAMESPACE

#endif // HADJUSTEDITDIALOG_P_H
