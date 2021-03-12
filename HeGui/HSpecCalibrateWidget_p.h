#pragma once

#include "HSpecCalibrateWidget.h"
#include "HAbstractTestWidget_p.h"

HE_GUI_BEGIN_NAMESPACE

class HSpecSampleChartView;
class HSpecFittingChartView;
class HSpecEnergyWidget;
class HSpecPelsWaveWidget;
class HSpecFittingWidget;
class ITestDetailWidget;

class HSpecCalibrateWidgetPrivate : public HAbstractTestWidgetPrivate
{
public:
    HSpecCalibrateWidgetPrivate();

public:
    ISpecCalibrate *calibrate = nullptr;
    HSpecSampleChartView *sampleView = nullptr;
    HSpecFittingChartView *ccdView = nullptr;
    HSpecEnergyWidget *energyWidget = nullptr;
    HSpecPelsWaveWidget *pelsWaveWidget = nullptr;
    HSpecFittingWidget *fittingWidget = nullptr;
    ITestDetailWidget *detailWidget = nullptr;

public:
    int fittingTimes = 0;
};

HE_GUI_END_NAMESPACE
