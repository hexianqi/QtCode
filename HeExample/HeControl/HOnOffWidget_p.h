#pragma once

#include "HOnOffWidget.h"

HE_BEGIN_NAMESPACE

class HOnOffWidgetPrivate
{
public:
    double x;
    bool runing = false;
    bool isOn = false;
    QTimer *timer = nullptr;
};

HE_END_NAMESPACE

