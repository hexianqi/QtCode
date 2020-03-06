#ifndef HCALLOUTCHARTITEM_P_H
#define HCALLOUTCHARTITEM_P_H

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

#endif // HCALLOUTCHARTITEM_P_H
