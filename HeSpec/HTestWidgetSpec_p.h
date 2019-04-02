#ifndef HTESTWIDGETSPEC_P_H
#define HTESTWIDGETSPEC_P_H

#include "HTestWidgetSpec.h"
#include "HeData/HDataGlobal.h"
#include "HeGui/HAbstractTestWidget_p.h"

HE_CONTROLLER_BEGIN_NAMESPACE
class ITestSpec;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE
class ISpecCalibrate;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE
class HSpecSampleWidget;
class HSpecEnergyWidget;
class HSpecFittingChartView;
class HSpecPelsWaveWidget;
class HSpecFittingLinearWidget;
class ITestSetWidget;
class IDetailWidget;
HE_GUI_END_NAMESPACE
HE_GUI_USE_NAMESPACE

class HTestWidgetSpecPrivate : public HAbstractTestWidgetPrivate
{
public:
    HTestWidgetSpecPrivate();

public:
    ITestSpec *testSpec;
    ISpecCalibrate *specCalibrate;

public:
    HSpecSampleWidget *sampleWidget;
    HSpecFittingChartView *ccdView;
    HSpecEnergyWidget *energyWidget;
    HSpecPelsWaveWidget *pelsWaveWidget;
    HSpecFittingLinearWidget *fittingWidget;
    ITestSetWidget *testSetWidget;
    IDetailWidget *detailWidget;

public:
    int fittingTimes = 0;
};

#endif // HTESTWIDGETSPEC_P_H
