#ifndef HTESTWIDGETDEMO_P_H
#define HTESTWIDGETDEMO_P_H

#include "HTestWidgetDemo.h"
#include "HeGui/HTestWidget_p.h"

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

class HTestWidgetDemoPrivate : public HTestWidgetPrivate
{
public:
    ISpecCalibrate *specCalibrate;

public:
    QTabWidget *tabWidget;
    HSpecSampleChartView *sampleView;
    HSpecFittingChartView *ccdView;
    HSpecEnergyWidget *energyWidget;
    HSpecPelsWaveWidget *pelsWaveWidget;
    HSpecFittingWidget *fittingWidget;
    ITestDetailWidget *detailWidget;
    ITestSetWidget *testSetWidget;
};

#endif // HTESTWIDGETDEMO_P_H
