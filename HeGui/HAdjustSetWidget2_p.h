#pragma once

#include "HAdjustSetWidget2.h"
#include "HAbstractTestSetWidget_p.h"

HE_GUI_BEGIN_NAMESPACE

class HAdjustSetWidget2Private : public HAbstractTestSetWidgetPrivate
{
public:
    bool autoIntegralTime = false;
};

HE_GUI_END_NAMESPACE
