#include "HGraphicsSpacerItem_p.h"
#include <QtGui/QPainter>
#include <QtWidgets/QStyleOptionGraphicsItem>

HE_BEGIN_NAMESPACE

HGraphicsSpacerItem::HGraphicsSpacerItem(int w, int h, QSizePolicy::Policy hPolicy, QSizePolicy::Policy vPolicy, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    d_ptr(new HGraphicsSpacerItemPrivate)
{
    d_ptr->width = w;
    d_ptr->height = h;
    d_ptr->sizePolicy = QSizePolicy(hPolicy, vPolicy);
}

HGraphicsSpacerItem::HGraphicsSpacerItem(HGraphicsSpacerItemPrivate &p, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    d_ptr(&p)
{
}

HGraphicsSpacerItem::~HGraphicsSpacerItem()
{
}

QSizeF HGraphicsSpacerItem::sizeHint(Qt::SizeHint which, const QSizeF &) const
{
    switch (which)
    {
    case Qt::MinimumSize:
        return QSizeF(60,60);
    case Qt::PreferredSize:
        return boundingRect().size();
    case Qt::MaximumSize:
        return QSizeF(10000,10000);
    default:
        return boundingRect().size();
    }
}

QRectF HGraphicsSpacerItem::boundingRect() const
{
    return d_ptr->rect;
}

void HGraphicsSpacerItem::setGeometry(const QRectF &value)
{
    prepareGeometryChange();
    d_ptr->rect = value;
    d_ptr->width = value.width();
    d_ptr->height = value.height();
    QGraphicsLayoutItem::setGeometry(value);
    setPos(value.topLeft());
}

void HGraphicsSpacerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->fillRect(option->rect,Qt::transparent);
}

HE_END_NAMESPACE
