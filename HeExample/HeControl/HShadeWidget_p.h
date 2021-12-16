#pragma once

#include "HShadeWidget.h"

HE_BEGIN_NAMESPACE

class HShadeWidgetPrivate
{
public:
    QColor background;
    double opacity;
    QWidget *mainWidget = nullptr;
};

HE_END_NAMESPACE
