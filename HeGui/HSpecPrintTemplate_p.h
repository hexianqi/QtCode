#pragma once

#include "HSpecPrintTemplate.h"
#include "HeData/HAbstractPrintTemplate_p.h"

class HSpecDiagramWidget;
class HCie1931Widget;
class HTm30SpdChartView;
class HTm30CvgWidget;
class HTm30RxhjWidget;
class HTm30RfiChartView;
class HTm30GamutWidget;
class HTm30RfRgChartView;

HE_BEGIN_NAMESPACE

class HSpecPrintTemplatePrivate : public HAbstractPrintTemplatePrivate
{
public:
    HSpecPrintTemplatePrivate();

public:
    HSpecDiagramWidget *specWidget = nullptr;
    HCie1931Widget *cieWidget = nullptr;
    HTm30SpdChartView *spdWidget = nullptr;
    HTm30CvgWidget *cvgWidget = nullptr;
    HTm30RxhjWidget *rxhjWidget = nullptr;
    HTm30RfiChartView *rfiWidget = nullptr;
    HTm30GamutWidget *gamutWidget = nullptr;
    HTm30RfRgChartView *rfrgWidget = nullptr;
    bool haveTM30 = true;
};

HE_END_NAMESPACE

