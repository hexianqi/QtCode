#ifndef HSPECENERGYWIDGET_P_H
#define HSPECENERGYWIDGET_P_H

#include "HSpecEnergyWidget.h"
#include "HeController/HControllerGlobal.h"
#include "HeData/HDataGlobal.h"

class HSpecDiagramWidget;
class HProgressBar;
class QHBoxLayout;

HE_CONTROLLER_BEGIN_NAMESPACE
class ITestSpec;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecEnergyWidgetPrivate
{
public:
    HSpecEnergyWidgetPrivate();

public:
    ITestSpec *testSpec;
    QStringList toolTipTypes;
    HSpecDiagramWidget *specWidget;
    HProgressBar *progressBar;
    QHBoxLayout *progressLayout;
};

HE_GUI_END_NAMESPACE

#endif // HSPECENERGYWIDGET_P_H
