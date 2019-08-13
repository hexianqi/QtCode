#ifndef HTILEDBACKGROUND_P_H
#define HTILEDBACKGROUND_P_H

#include "HTiledBackground.h"

HE_CONTROL_BEGIN_NAMESPACE

class HTiledBackgroundPrivate
{
public:
    QColor color1 = QColor(255, 255, 255);
    QColor color2 = QColor(220, 220, 220);
    int size = 32;
    QPixmap pixmap;
};

HE_CONTROL_END_NAMESPACE

#endif // HTILEDBACKGROUND_P_H
