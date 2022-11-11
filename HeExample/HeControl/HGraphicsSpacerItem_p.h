#pragma once

#include "HGraphicsSpacerItem.h"

HE_BEGIN_NAMESPACE

class HGraphicsSpacerItemPrivate
{
public:
    double width;
    double height;
    QSizePolicy sizePolicy;
    QRectF rect;
};

HE_END_NAMESPACE

