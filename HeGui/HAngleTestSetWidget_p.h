#pragma once

#include "HAngleTestSetWidget.h"
#include "HAbstractTestSetWidget_p.h"

HE_BEGIN_NAMESPACE

class HAngleTestSetWidgetPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    bool autoLuminousGears = true;
};

HE_END_NAMESPACE
