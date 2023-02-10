#pragma once

#include "HSlideButtonGroup.h"

HE_BEGIN_NAMESPACE

class HSlideButtonGroupPrivate
{
public:
    HSlideButtonGroup::State state = HSlideButtonGroup::UnPressed;
    QList<QPixmap> images;
    QList<QRect> rects;
    int widthChangeValue = 0;
    int angle = 0;
    int index = -1;
    QTimer *timer;
};

HE_END_NAMESPACE

