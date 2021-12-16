#pragma once

#include "HAdjustSetWidget.h"
#include "HAbstractTestSetWidget_p.h"

HE_BEGIN_NAMESPACE

class HAdjustSetWidgetPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    bool autoIntegralTime = false;
};

HE_END_NAMESPACE
