#pragma once

#include "HProcessDisplayWidget.h"

HE_BEGIN_NAMESPACE

class HProcessDisplayWidgetPrivate
{
public:
    QStringList processs;
    int currentStep{1};
    QColor lineColor{"#C0C4CC"};
    QColor completedStepsColor{"#41CD52"};
    QColor uncompleteStepColor{"#333333"};
    QColor currentStepColor{"#FC5531"};
};

HE_END_NAMESPACE

