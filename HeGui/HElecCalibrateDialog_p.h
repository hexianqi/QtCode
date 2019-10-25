#ifndef HELECCALIBRATEDIALOG_P_H
#define HELECCALIBRATEDIALOG_P_H

#include "HElecCalibrateDialog.h"
#include "HeController/HControllerGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IElecCalibrateCollection;
class ITestElec;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HElecCalibrateItemWidget;

class HElecCalibrateDialogPrivate
{
public:
    HElecCalibrateDialogPrivate();

public:
    IElecCalibrateCollection *calibrate = nullptr;
    ITestElec *testElec = nullptr;
    IModel *model = nullptr;
    HElecCalibrateItemWidget *currentWidget = nullptr;
    bool loop = false;
    int module = -1;
    int index = -1;
};

HE_GUI_END_NAMESPACE

#endif // HELECCALIBRATEDIALOG_P_H
