#ifndef HMULTISTYLEBUTTON_P_H
#define HMULTISTYLEBUTTON_P_H

#include "HMultiStyleButton.h"
#include <QLabel>

HE_CONTROL_BEGIN_NAMESPACE

class IEventFilter;

class HMultiStyleButtonPrivate
{
public:
    QPixmap background;
    int borderRadius = 5;
    int borderWidth = 2;
    QColor borderColor = QColor(180, 180, 180);
    QString text;
    QFont textFont;
    Qt::Alignment textAlign = Qt::AlignCenter;
    QColor textColor = QColor(230, 230, 230);
    bool showSuperText;
    QString superText;
    QFont superTextFont;
    Qt::Alignment superTextAlign = Qt::AlignTop | Qt::AlignTop;
    QColor superTextColor = QColor(230, 230, 230);
    QColor normalColor = QColor(80, 80, 80);
    QColor pressedColor = QColor(30, 30, 30);
    HMultiStyleButton::ColorMode colorMode = HMultiStyleButton::ColorMode_Normal;
    bool moveEnable = false;
    bool pressed = false;
    IEventFilter *filter = nullptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HMULTISTYLEBUTTON_P_H
