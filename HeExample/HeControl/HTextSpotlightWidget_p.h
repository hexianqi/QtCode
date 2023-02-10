#pragma once

#include "HTextSpotlightWidget.h"

HE_BEGIN_NAMESPACE

class HTextSpotlightWidgetPrivate
{
public:
    QString text;
    QTimer *timer;
    QRect textRect;
    int changeValue = 0;
    bool runDirectionIsRight = true;
};

HE_END_NAMESPACE

