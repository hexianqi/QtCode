#pragma once

#include "HTestSetWidget2000AC.h"
#include "HeGui/HAbstractTestSetWidget_p.h"

class HTestSetWidget2000ACPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    bool autoIntegralTime = false;
    QTimer *timerContinue = nullptr;
};
