#pragma once

#include "HReelWidget.h"

HE_BEGIN_NAMESPACE

class HReelWidgetPrivate
{
public:
    QPixmap pixmap;
    int rateFactor = 5;
    uint lastNumber = 0;
    uint currentNumber = 1;
    bool isRuning = false;
    QTimer *timer = nullptr;
    HReelWidget::State state = HReelWidget::NoRun;
    QRect currentImageRect;
    QRect lastImageRect;
};

HE_END_NAMESPACE

