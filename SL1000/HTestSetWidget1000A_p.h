#pragma once

#include "HTestSetWidget1000A.h"
#include "HeGui/HAbstractTestSetWidget_p.h"

class HTestSetWidget1000APrivate : public HAbstractTestSetWidgetPrivate
{
public:
    bool first = true;
    bool autoIntegralTime = false;
    bool autoLuminousGears = true;
    QTimer *timerContinue = nullptr;
    QTimer *timerInterval = nullptr;
};
