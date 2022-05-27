#pragma once

#include "HNavButton.h"

HE_BEGIN_NAMESPACE

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
    HControlType::Position trianglePosition = HControlType::Position_Right;
    QColor triangleColor = Qt::white;
    bool showIcon = false;
    int iconSpace = 10;
    QSize iconSize = QSize(16, 16);
    QPixmap iconNormal;
    QPixmap iconHover;
    QPixmap iconCheck;
    bool showLine = true;
    int lineSpace = 0;
    int lineWidth = 5;
    HControlType::Position linePosition = HControlType::Position_Left;
    QColor lineColor = QColor(0, 187, 158);
    QColor normalBackground = QColor(230, 230, 230);
    QColor hoverBackground = QColor(130, 130, 130);
    QColor checkBackground = QColor(80, 80, 80);
    QColor normalTextColor = QColor(100, 100, 100);
    QColor hoverTextColor = Qt::white;
    QColor checkTextColor = Qt::white;
    QBrush normalBackgroundBrush = Qt::NoBrush;
    QBrush hoverBackgroundBrush = Qt::NoBrush;
    QBrush checkBackgroundBrush = Qt::NoBrush;
    bool hover = false;
};

HE_END_NAMESPACE
