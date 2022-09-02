#pragma once

#include "HGraphicsObject.h"

HE_BEGIN_NAMESPACE

class HGraphicsObjectPrivate
{
public:
    HGraphicsObject::ItemFix itemFix = HGraphicsObject::FixNot;
    QSizeF itemSize = QSizeF(0, 0);
    QSizeF minimumSizeHint = QSizeF(0, 0);
    bool resizing = false;
    QVector<int> resizePos = { 9, 6, 3 };
};

HE_END_NAMESPACE

