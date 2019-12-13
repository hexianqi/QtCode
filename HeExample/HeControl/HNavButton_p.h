#ifndef HNAVBUTTON_P_H
#define HNAVBUTTON_P_H

#include "HNavButton.h"

HE_CONTROL_BEGIN_NAMESPACE

class HNavButtonPrivate
{
public:
    int paddingLeft = 20;
    int paddingRight = 5;
    int paddingTop = 5;
    int paddingBottom = 5;
    Qt::Alignment textAlign = Qt::AlignCenter;
    bool showTriangle = false;
    int triangleLen = 5;
    HNavButton::Position trianglePosition = HNavButton::PositionRight;
    QColor triangleColor = Qt::black;
    bool showIcon = false;
    int iconSpace = 10;
    QSize iconSize = QSize(16, 16);
    QPixmap iconNormal;
    QPixmap iconHover;
    QPixmap iconCheck;
    bool showLine = true;
    int lineSpace = 0;
    int lineWidth = 5;
    HNavButton::Position linePosition = HNavButton::PositionLeft;
    QColor lineColor = QColor(0, 187, 158);
    QColor normalBackground = QColor(230, 230, 230);
    QColor hoverBackground = QColor(130, 130, 130);
    QColor checkBackground = QColor(80, 80, 80);
    QColor normalTextColor = QColor(100, 100, 100);
    QColor hoverTextColor = Qt::black;
    QColor checkTextColor = Qt::black;
    QBrush normalBackgroundBrush = Qt::NoBrush;
    QBrush hoverBackgroundBrush = Qt::NoBrush;
    QBrush checkBackgroundBrush = Qt::NoBrush;
    bool hover = false;
};

HE_CONTROL_END_NAMESPACE

#endif // HNAVBUTTON_P_H
