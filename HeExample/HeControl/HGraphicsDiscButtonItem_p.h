#pragma once

#include "HGraphicsDiscButtonItem.h"
#include "HGraphicsObject_p.h"

HE_BEGIN_NAMESPACE

class HGraphicsDiscButtonItemPrivate : public HGraphicsObjectPrivate
{
public:
    HGraphicsDiscButtonItemPrivate();

public:
    double boardRadius = 0.0;
    double circularRadius = 0.0;
    QPointF boardCenter = QPointF(0.0, 0.0);
    HGraphicsDiscButtonItem::ButtonType pressButtonType = HGraphicsDiscButtonItem::Button_None;
};

HE_END_NAMESPACE

