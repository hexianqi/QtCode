#pragma once

#include "HTrendTestSetWidget.h"
#include "HAbstractTestSetWidget_p.h"

HE_BEGIN_NAMESPACE

class HTrendTestSetWidgetPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    bool first = true;
    QTimer *timerContinue = nullptr;
    QTimer *timerInterval = nullptr;
};

HE_END_NAMESPACE
