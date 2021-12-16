#pragma once

#include "HSpecSampleChartView.h"
#include "HePlugin/HVernierChartView_p.h"

HE_BEGIN_NAMESPACE

class ITestSpec;

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

HE_END_NAMESPACE
