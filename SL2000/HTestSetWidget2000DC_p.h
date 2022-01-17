#pragma once

#include "HTestSetWidget2000DC.h"
#include "HeGui/HAbstractTestSetWidget_p.h"

class HTestSetWidget2000DCPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    bool first = true;
    bool autoIntegralTime = false;
    bool autoLuminousGears = true;
    QTimer *timerContinue = nullptr;
    QTimer *timerInterval = nullptr;
};
