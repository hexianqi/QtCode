#pragma once

#include "HSpecPrintTemplate.h"
#include "HeData/HAbstractPrintTemplate_p.h"

class HSpecDiagramWidget;
class HCie1931Widget;

HE_GUI_BEGIN_NAMESPACE

class HE_GUI_EXPORT HSpecPrintTemplatePrivate : public HAbstractPrintTemplatePrivate
{
public:
    HSpecPrintTemplatePrivate();

public:
    HSpecDiagramWidget *specWidget = nullptr;
    HCie1931Widget *cieWidget = nullptr;
};

HE_GUI_END_NAMESPACE

