#include "HGraphicsFlowLayout_p.h"

HE_BEGIN_NAMESPACE

HGraphicsFlowLayout::HGraphicsFlowLayout(QGraphicsLayoutItem *parent) :
    QGraphicsLayout(parent),
    d_ptr(new HGraphicsFlowLayoutPrivate)
{
}

HGraphicsFlowLayout::HGraphicsFlowLayout(HGraphicsFlowLayoutPrivate &p, QGraphicsLayoutItem *parent) :
    QGraphicsLayout(parent),
    d_ptr(&p)
{
}

HGraphicsFlowLayout::~HGraphicsFlowLayout()
{
    for (auto item : d_ptr->items)
    {
        if (item->ownedByLayout())
            delete item;
    }
}

QSizeF HGraphicsFlowLayout::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    QSizeF size;
    for (auto item : d_ptr->items)
    {
        QSizeF itemSize;
        switch (which)
        {
        case Qt::MinimumSize:
            itemSize = item->minimumSize();
            break;
        case Qt::PreferredSize:
            itemSize = item->preferredSize();
            break;
        case Qt::MaximumSize:
            itemSize = item->maximumSize();
            break;
        default:
            itemSize = constraint;
        }
        size = size.expandedTo(itemSize);
    }
    size += QSize(20, 20);
    size.setHeight(size.height() * 4);
    if(size.height() < 100)
        size.setHeight(100);
    return size;
}

int HGraphicsFlowLayout::count() const
{
    return d_ptr->items.size();
}

void HGraphicsFlowLayout::setGeometry(const QRectF &rect)
{
    qreal left, top, right, bottom, lineHeight = 0;
    getContentsMargins(&left, &top, &right, &bottom); // 获取布局目前的上下左右边距值
    auto effectiveRect = rect.adjusted(left, top, -right, -bottom);
    auto x = effectiveRect.x();
    auto y = effectiveRect.y();
    for (auto item : d_ptr->items)
    {
        auto spaceX = 15.0;
        auto spaceY = 15.0;
        auto size = item->preferredSize();
        auto nextX = x + size.width() + spaceX;
        if (nextX - spaceX > effectiveRect.right() && lineHeight > 0)
        {
            x = effectiveRect.x();
            y = y + lineHeight + spaceY;
            nextX = x + size.width() + spaceX;
            lineHeight = 0;
        }
        item->setGeometry(QRectF(QPointF(x, y), size));
        x = nextX;
        lineHeight = qMax(lineHeight, size.height());
    }
}

void HGraphicsFlowLayout::removeAt(int index)
{
    if (index >= 0 && index < d_ptr->items.size())
    {
        auto item = d_ptr->items.takeAt(index);
        delete item;
        invalidate();
    }
}

QGraphicsLayoutItem *HGraphicsFlowLayout::itemAt(int index) const
{
    return (index >= 0 && index < d_ptr->items.size()) ? d_ptr->items.at(index) : nullptr;
}

void HGraphicsFlowLayout::addItem(QGraphicsLayoutItem *item)
{
    d_ptr->items.append(item);
    invalidate();
}

HE_END_NAMESPACE
