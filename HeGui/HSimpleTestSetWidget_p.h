#pragma once

#include "HSimpleTestSetWidget.h"
#include "HAbstractTestSetWidget_p.h"

HE_BEGIN_NAMESPACE

class HSimpleTestSetWidgetPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    bool autoIntegralTime = false;
};

HE_END_NAMESPACE
