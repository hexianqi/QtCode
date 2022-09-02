#pragma once

#include "HGraphicsColorBoardItem.h"
#include "HGraphicsObject_p.h"
#include <QtGui/QGradient>

HE_BEGIN_NAMESPACE

class HGraphicsColorBoardItemPrivate : public HGraphicsObjectPrivate
{
public:
    HGraphicsColorBoardItemPrivate();

public:
    int value = 255;
    QConicalGradient conicalGradient;
    QRadialGradient radialGradient;
    QPixmap boardPixmap;
    double boardRadius = 0.0;
    QPointF boardCenter = QPointF(0.0, 0.0);
    QPointF pos = QPointF(0.0, 0.0);
};

HE_END_NAMESPACE

