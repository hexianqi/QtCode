#ifndef HGRAPHICSCALLOUTITEM_P_H
#define HGRAPHICSCALLOUTITEM_P_H

#include "HGraphicsCalloutItem.h"
#include "HGraphicsItem_p.h"

class HGraphicsCalloutItemPrivate : public HGraphicsItemPrivate
{
public:
    QChart *chart;
    QString text;
    QRectF textRect;
/*    QRectF m_rect;
    QPointF anchor;
    QFont m_font*/;


};

#endif // HGRAPHICSCALLOUTITEM_P_H
