#ifndef HSPECSAMPLECHARTVIEW_P_H
#define HSPECSAMPLECHARTVIEW_P_H

#include "HSpecSampleChartView.h"
#include "HeController/HControllerGlobal.h"
#include "HePlugin/HVernierChartView_p.h"

HE_CONTROLLER_BEGIN_NAMESPACE
class ITestSpec;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecSampleChartViewPrivate : public HVernierChartViewPrivate
{
public:
    HSpecSampleChartViewPrivate();

public:
    ITestSpec *testSpec;

public:
    bool enablePeak = true;
    QVector<double> verniers;
};

HE_GUI_END_NAMESPACE

#endif // HSPECSAMPLECHARTVIEW_P_H
