#pragma once

#include "HTestWidgetDemo.h"
#include "HeGui/HTestWidget2_p.h"

class QTabWidget;

HE_GUI_BEGIN_NAMESPACE
class HSpecSampleChartView;
class HSpecFittingChartView;
class HSpecEnergyWidget;
class HSpecPelsWaveWidget;
class HSpecFittingWidget;
class ITestSetWidget;
class ITestDetailWidget;
HE_GUI_END_NAMESPACE

class HTestWidgetDemoPrivate : public HTestWidget2Private
{
public:
    ISpecCalibrate *specCalibrate;

public:
    QAction *actionImport;
    QTabWidget *tabWidget;
    HSpecSampleChartView *sampleView;
    HSpecFittingChartView *ccdView;
    HSpecEnergyWidget *energyWidget;
    HSpecPelsWaveWidget *pelsWaveWidget;
    HSpecFittingWidget *fittingWidget;
    ITestDetailWidget *detailWidget;
    ITestSetWidget *testSetWidget;
};
