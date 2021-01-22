#pragma once

#include "HTestSetWidget2100DC.h"
#include "HeGui/HAbstractTestSetWidget_p.h"

class HTestSetWidget2100DCPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    bool autoIntegralTime = false;
    QTimer *timerContinue = nullptr;
    QTimer *timerInterval = nullptr;
};



