#pragma once

#include "HNinePatchPainter.h"
#include <QtCore/QMargins>
#include <QtGui/QPixmap>

class HNinePatchPainterPrivate
{
public:
    QMargins margins = QMargins(50, 50, 50, 50);
    bool stretchHorizontal = true;
    bool stretchVertical = true;
    QPixmap background;
    bool rebuildPixmap = true;

    QPixmap leftPixmap;        // 左边的子图
    QPixmap topLeftPixmap;     // 左上角的子图
    QPixmap topPixmap;         // 顶部的子图
    QPixmap topRightPixmap;    // 右上角的子图
    QPixmap rightPixmap;       // 右边的子图
    QPixmap bottomRightPixmap; // 右下角的子图
    QPixmap bottomPixmap;      // 底部的子图
    QPixmap bottomLeftPixmap;  // 左下角的子图
    QPixmap centerPixmap;      // 中间的子图
};
