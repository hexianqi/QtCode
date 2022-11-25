#pragma once

#include "HLineShadowWidget.h"

HE_BEGIN_NAMESPACE

class HLineShadowWidgetPrivate
{
public:
    int lineLength = 30;
    int shadowLength = 40;
    QColor shadowColor = Qt::white;
};

HE_END_NAMESPACE

