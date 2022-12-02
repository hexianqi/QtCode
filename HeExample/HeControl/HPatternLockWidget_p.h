#pragma once

#include "HPatternLockWidget.h"

HE_BEGIN_NAMESPACE

class HPatternLockWidgetPrivate
{
public:
    int number = 0;
    int lastHoverIndex = -1;
    bool isUpdateCircular = true;
    bool mouseInCircular = false;
    int currentOffset = 0;
    double radiu = 0.0;
    QPoint settingMousPos;
    HPatternLockWidget::PatternLockState patterneLockState = HPatternLockWidget::NotSet;
    QVector<HPatternLockWidget::CircularState> circularStates;
    QVector<QRect> circularRects;
    QVector<int> sets;
    QTimer *hoverTimer;
};

HE_END_NAMESPACE

