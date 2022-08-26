#pragma once

#include "HGraphicsPixmapItem.h"

HE_BEGIN_NAMESPACE

class HGraphicsPixmapItemPrivate
{
public:
    QPixmap pixmap;
    QString title;
    QColor textColor = Qt::red;
    QSizeF itemSize = QSizeF(0, 0);
    bool resizing = false;          // 是否正在改变大小的过程中
    QVector<int> resizePos = { 9, 6, 3 };
};

HE_END_NAMESPACE

