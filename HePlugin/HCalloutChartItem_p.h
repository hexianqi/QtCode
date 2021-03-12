#pragma once

#include "HCalloutChartItem.h"
#include "HGraphicsItem_p.h"
#include <QtGui/QFont>

class HCalloutChartItemPrivate : public HGraphicsItemPrivate
{
public:
    QChart *chart;
    QString text;
    QRectF textRect;
    QFont font;
    QRectF rect;
    QPointF anchor;
};
