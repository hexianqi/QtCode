#pragma once

#include "HAnglePrintTemplate.h"
#include "HeData/HAbstractPrintTemplate_p.h"

class HDynamicChartView;
class HPolarChartView;

HE_BEGIN_NAMESPACE

class HAnglePrintTemplatePrivate : public HAbstractPrintTemplatePrivate
{
public:
    HAnglePrintTemplatePrivate();

public:
    HDynamicChartView *cartesianChartView = nullptr;
    HPolarChartView *polarChartView = nullptr;
};

HE_END_NAMESPACE

