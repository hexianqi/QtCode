#pragma once

#include "HSoundSlider.h"
#include <QtGui/QBitmap>

HE_BEGIN_NAMESPACE

class HSoundSliderPrivate
{
public:
    bool muted = false;
    QList<QColor> colors;
    bool sliding = false;       // Whether we are currently sliding by user action
    bool mouseOutside = true;   // Whether the mouse is outside or inside the Widget
    int oldvalue = 0;           // Store the old Value before changing
    int paddingLeft = 6;
    int paddingRight = 6;
    bool rebuild = true;
    QPixmap outside;
    QPixmap progress1;
    QPixmap progress2;
    QColor background;
    QColor foreground;
    QFont font;
    QBitmap mask;
};

HE_END_NAMESPACE

