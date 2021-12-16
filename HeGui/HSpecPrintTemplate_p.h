#pragma once

#include "HSpecPrintTemplate.h"
#include "HeData/HAbstractPrintTemplate_p.h"

class HSpecDiagramWidget;
class HCie1931Widget;

HE_BEGIN_NAMESPACE

class HSpecPrintTemplatePrivate : public HAbstractPrintTemplatePrivate
{
public:
    HSpecPrintTemplatePrivate();

public:
    HSpecDiagramWidget *specWidget = nullptr;
    HCie1931Widget *cieWidget = nullptr;
};

HE_END_NAMESPACE

