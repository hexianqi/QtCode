#include "HPromotion.h"

uint qHash(const QPoint &key)
{
    return qHash(QPair<int, int>(key.x(), key.y()));
}

bool operator<(QPointF p1, QPointF p2)
{
    return p1.x() < p2.x();
}
