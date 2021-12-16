#pragma once

#include "HSpecCalibrateSetWidget.h"
#include "HAbstractTestSetWidget_p.h"

HE_BEGIN_NAMESPACE

class HSpecCalibrateSetWidgetPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    bool autoIntegralTime = false;
};

HE_END_NAMESPACE
