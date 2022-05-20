#pragma once

#include "HAngleTestDetailWidget.h"
#include "HAbstractTestDetailWidget_p.h"

HE_BEGIN_NAMESPACE

class HAngleTestDetailWidgetPrivate : public HAbstractTestDetailWidgetPrivate
{
public:
    HAngleTestDetailWidgetPrivate();

public:
    QString css;
};

HE_END_NAMESPACE
