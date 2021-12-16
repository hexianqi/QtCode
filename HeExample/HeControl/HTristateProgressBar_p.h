#pragma once

#include "HTristateProgressBar.h"

HE_BEGIN_NAMESPACE

class HTristateProgressBarPrivate
{
public:
    int value1 = 10;
    int value2 = 10;
    int value3 = 10;
    QColor color1 = QColor(34, 163, 169);
    QColor color2 = QColor(255, 192, 1);
    QColor color3 = QColor(214, 77, 84);
    int radius = 0;
    bool autoRadius = true;
    bool autoFont = true;
    bool showValue = true;
    bool showPercent= true;
    double borderWidth = 0.0;
    QColor background = QColor(40, 45, 48);
    QColor borderColor = QColor(250, 250, 250);
    QColor textColor  = QColor(250, 250, 250);
};

HE_END_NAMESPACE
