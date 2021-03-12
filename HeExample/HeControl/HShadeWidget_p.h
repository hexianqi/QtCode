#pragma once

#include "HShadeWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class HShadeWidgetPrivate
{
public:
    QColor background;
    double opacity;
    QWidget *mainWidget = nullptr;
};

HE_CONTROL_END_NAMESPACE
