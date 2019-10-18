#ifndef HELECCALIBRATEDIALOG_P_H
#define HELECCALIBRATEDIALOG_P_H

#include "HElecCalibrateDialog.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IElecCalibrateCollection;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HElecCalibrateDialogPrivate
{
public:
    HElecCalibrateDialogPrivate();

public:
    IElecCalibrateCollection *calibrate = nullptr;
};

HE_GUI_END_NAMESPACE

#endif // HELECCALIBRATEDIALOG_P_H
