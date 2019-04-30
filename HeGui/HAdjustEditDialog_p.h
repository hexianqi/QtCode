#ifndef HADJUSTEDITDIALOG_P_H
#define HADJUSTEDITDIALOG_P_H

#include "HAdjustEditDialog.h"
#include "HeController/HControllerGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IDataFactory;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
class ITestData;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecEnergyWidget;

class HAdjustEditDialogPrivate
{
public:
    HAdjustEditDialogPrivate();

public:
    IDataFactory *factory = nullptr;
    IAdjust *data = nullptr;
    IModel *model;
    ITestData *testData;
    QStringList optionals;
    QStringList selecteds;
    QStringList unselecteds;

public:
    HSpecEnergyWidget *energyWidget;
    ITestSetWidget *testSetWidget;
};

HE_GUI_END_NAMESPACE

#endif // HADJUSTEDITDIALOG_P_H
