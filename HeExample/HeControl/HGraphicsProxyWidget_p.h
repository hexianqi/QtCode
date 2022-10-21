#pragma once

#include "HGraphicsProxyWidget.h"

HE_BEGIN_NAMESPACE

class HGraphicsProxyWidgetPrivate
{
public:
    QSizeF itemSize = QSizeF(100, 100);
    QSizeF minimumSizeHint = QSizeF(0, 0);
    bool resizing = false;
    bool grabbedByWidget = false;
    QVector<int> resizePos = { 9, 6, 3 };

//    QPointF dragPosition;

};

HE_END_NAMESPACE

