#ifndef HLIGHTBUTTON_P_H
#define HLIGHTBUTTON_P_H

#include "HLightButton.h"

HE_CONTROL_BEGIN_NAMESPACE

class IEventFilter;

class HLightButtonPrivate
{
public:
    QString text;
    QColor textColor = QColor(255, 255, 255);
    QColor borderOutColorStart = QColor(255, 255, 255);
    QColor borderOutColorEnd = QColor(166, 166, 166);
    QColor borderInColorStart = QColor(166, 166, 166);
    QColor borderInColorEnd = QColor(255, 255, 255);
    QColor background = QColor(100, 184, 255);
    QColor overlayColor = QColor(255, 255, 255);
    bool enableMove = false;
    bool showOverlay = true;
    IEventFilter *filter = nullptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HLIGHTBUTTON_P_H
