#pragma once

#include "HLightButton.h"

HE_BEGIN_NAMESPACE

class IEventFilter;

class HLightButtonPrivate
{
public:
    QString text;
    QColor textColor = QColor(255, 255, 255);
    QColor alarmColor = QColor(255, 107, 107);
    QColor normalColor = QColor(10, 10, 10);
    QColor borderOutColorStart = QColor(255, 255, 255);
    QColor borderOutColorEnd = QColor(166, 166, 166);
    QColor borderInColorStart = QColor(166, 166, 166);
    QColor borderInColorEnd = QColor(255, 255, 255);
    QColor background = QColor(100, 184, 255);
    QColor overlayColor = QColor(255, 255, 255);
    bool moveEnable = true;
    bool showRect = false;
    bool showOverlay = true;
    bool isAlarm = false;
    IEventFilter *filter = nullptr;
    QTimer *timer = nullptr;
};

HE_END_NAMESPACE
