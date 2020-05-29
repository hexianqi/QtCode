#ifndef HSPECENERGYWIDGET_P_H
#define HSPECENERGYWIDGET_P_H

#include "HSpecEnergyWidget.h"
#include "HeData/HDataGlobal.h"

class HSpecDiagramWidget;
class HProgressBar;
class QHBoxLayout;

HE_DATA_BEGIN_NAMESPACE
class ITestData;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecEnergyWidgetPrivate
{
public:
    HSpecEnergyWidgetPrivate();

public:
    ITestData *testData = nullptr;
    HSpecDiagramWidget *specWidget = nullptr;
    QHBoxLayout *progressLayout = nullptr;
    QList<HProgressBar *> progressBars;
    QStringList toolTipTypes;
};

HE_GUI_END_NAMESPACE

#endif // HSPECENERGYWIDGET_P_H
