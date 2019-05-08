#ifndef HSPECENERGYWIDGET_P_H
#define HSPECENERGYWIDGET_P_H

#include "HSpecEnergyWidget.h"
#include "HeData/HDataGlobal.h"

class HSpecDiagramWidget;
class HProgressBar;
class QHBoxLayout;

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

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
