#ifndef HSPECCALIBRATEWIDGET_P_H
#define HSPECCALIBRATEWIDGET_P_H

#include "HSpecCalibrateWidget.h"
#include "HAbstractTestWidget_p.h"

HE_CONTROLLER_BEGIN_NAMESPACE
class ITestSpec;
HE_CONTROLLER_END_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecSampleChartView;
class HSpecFittingChartView;
class HSpecEnergyWidget;
class HSpecPelsWaveWidget;
class HSpecFittingLinearWidget;
class IDetailWidget;

class HSpecCalibrateWidgetPrivate : public HAbstractTestWidgetPrivate
{
public:
    HSpecCalibrateWidgetPrivate();

public:
    ITestSpec *testSpec;
    ISpecCalibrate *specCalibrate;

public:
    HSpecSampleChartView *sampleView;
    HSpecFittingChartView *ccdView;
    HSpecEnergyWidget *energyWidget;
    HSpecPelsWaveWidget *pelsWaveWidget;
    HSpecFittingLinearWidget *fittingWidget;
    ITestSetWidget *testSetWidget;
    IDetailWidget *detailWidget;

public:
    int fittingTimes = 0;
};

HE_GUI_END_NAMESPACE

#endif // HSPECCALIBRATEWIDGET_P_H
