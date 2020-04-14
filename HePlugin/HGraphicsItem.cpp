#include "HGraphicsItem_p.h"

HGraphicsItem::HGraphicsItem(QGraphicsItem *parent) :
    QGraphicsItem(parent),
    d_ptr(new HGraphicsItemPrivate)
{
}

HGraphicsItem::HGraphicsItem(HGraphicsItemPrivate &p, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    d_ptr(&p)
{
}

HGraphicsItem::~HGraphicsItem() = default;

