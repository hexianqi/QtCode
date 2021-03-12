#pragma once

#include "HButtonProgressBar.h"
#include "HAbstractProgress_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HButtonProgressBarPrivate : public HAbstractProgressPrivate
{
public:
    QColor background = QColor(34, 163, 169);
    int lineWidth = 8;
    QColor lineColor = QColor(250, 250, 250);
    int borderWidth = 0;
    int borderRadius = 5;
    QColor borderColor = QColor(14, 153, 160);

public:
    int status = 0;         // 状态
    int tempWidth = 0;      // 动态改变宽度
    QTimer *timer;
};

HE_CONTROL_END_NAMESPACE
