#ifndef HSPECSAMPLECHARTVIEW_P_H
#define HSPECSAMPLECHARTVIEW_P_H

#include "HSpecSampleChartView.h"
#include "HeData/HDataGlobal.h"
#include "HePlugin/HVernierChartView_p.h"

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecSampleChartViewPrivate : public HVernierChartViewPrivate
{
public:
    HSpecSampleChartViewPrivate();

public:
    ITestSpec *testSpec;

public:
    bool enablePeak = true;
    QList<double> verniers;
};

HE_GUI_END_NAMESPACE

#endif // HSPECSAMPLECHARTVIEW_P_H
