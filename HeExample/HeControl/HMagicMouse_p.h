#pragma once

#include "HMagicMouse.h"

HE_BEGIN_NAMESPACE

class HMagicMousePrivate
{
public:
    double angle = 0;
    QColor bodyColor = QColor(29, 89, 115);
    QColor eyeColor = QColor(30, 30, 30);
    QColor eyeballColor = QColor(255, 255, 255);
    QColor noseColor = QColor(30, 30, 30);
    QColor earColor = QColor(86, 190, 193);
    QColor tailColor = QColor(168, 126, 166);
};

HE_END_NAMESPACE
