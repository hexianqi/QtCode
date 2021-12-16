#pragma once

#include "HPanelItem.h"

HE_BEGIN_NAMESPACE

class HPanelItemPrivate
{
public:
    int borderWidth = 3;
    int borderRadius = 5;
    QColor borderColor = QColor(21, 156, 119);
    QColor borderDisableColor = QColor(180, 180, 180);
    int titleHeight = 30;
    QString titleText;
    QFont titleFont;
    Qt::Alignment titleAlignment = Qt::AlignCenter;
    QColor titleColor = Qt::white;
    QColor titleDisableColor = QColor(230, 230, 230);
    bool alarm = false;
    QColor alarmTextColor = QColor(250, 250, 250);
    QColor alarmDarkColor = QColor(205, 0, 0);
    QColor alarmNormalColor = QColor(80, 80, 80);
    bool dark = false;
    QTimer *timer = nullptr;
};

HE_END_NAMESPACE
