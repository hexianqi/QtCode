#ifndef HSPECCALIBRATEWIDGET_P_H
#define HSPECCALIBRATEWIDGET_P_H

#include "HSpecCalibrateWidget.h"
#include "HAbstractTestWidget_p.h"

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
HE_DATA_END_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecSampleChartView;
class HSpecFittingChartView;
class HSpecEnergyWidget;
class HSpecPelsWaveWidget;
class HSpecFittingLinearWidget;
class ITestDetailWidget;

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
    ITestDetailWidget *detailWidget;

public:
    int fittingTimes = 0;
};

HE_GUI_END_NAMESPACE

#endif // HSPECCALIBRATEWIDGET_P_H
