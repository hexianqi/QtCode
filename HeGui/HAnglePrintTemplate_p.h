#pragma once

#include "HAnglePrintTemplate.h"
#include "HeData/HAbstractPrintTemplate_p.h"

class HDynamicChartView;

HE_BEGIN_NAMESPACE

class HAngleChartView;

class HAnglePrintTemplatePrivate : public HAbstractPrintTemplatePrivate
{
public:
    HAnglePrintTemplatePrivate();

public:
    HDynamicChartView *cartesianChartView = nullptr;
    HAngleChartView *polarChartView = nullptr;
};

HE_END_NAMESPACE

