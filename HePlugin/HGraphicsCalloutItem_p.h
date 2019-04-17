#ifndef HGRAPHICSCALLOUTITEM_P_H
#define HGRAPHICSCALLOUTITEM_P_H

#include "HGraphicsCalloutItem.h"
#include "HGraphicsItem_p.h"
#include <QtGui/QFont>

class HGraphicsCalloutItemPrivate : public HGraphicsItemPrivate
{
public:
    QChart *chart;
    QString text;
    QRectF textRect;
    QFont font;
    QRectF rect;
    QPointF anchor;
};

#endif // HGRAPHICSCALLOUTITEM_P_H
