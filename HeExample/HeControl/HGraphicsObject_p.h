#pragma once

#include "HGraphicsObject.h"

HE_BEGIN_NAMESPACE

class HGraphicsObjectPrivate
{
public:
    QSizeF itemSize = QSizeF(0, 0);
    bool resizing = false;
    QVector<int> resizePos = { 9, 6, 3 };
};

HE_END_NAMESPACE

