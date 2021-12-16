#pragma once

#include "HIVTestSetWidget.h"
#include "HAbstractTestSetWidget_p.h"

HE_BEGIN_NAMESPACE

class HIVTestSetWidgetPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    double current = 1.0;
    double from = 1.0;
    double to = 100.0;
    double interval = 1.0;
};

HE_END_NAMESPACE
