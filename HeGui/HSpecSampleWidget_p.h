#pragma once

#include "HSpecSampleWidget.h"
#include "HePlugin/HVernierWidget_p.h"

HE_BEGIN_NAMESPACE

class ITestSpec;

class HSpecSampleWidgetPrivate : public HVernierWidgetPrivate
{
public:
    HSpecSampleWidgetPrivate();

public:
    ITestSpec *testSpec;

public:
    bool enablePeak = true;
    QList<bool> curveVisibles;
    QList<double> verniers;
};

HE_END_NAMESPACE
