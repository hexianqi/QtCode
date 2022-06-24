#include "HCanvasItem_p.h"

HCanvasItem::HCanvasItem() :
    d_ptr(new HCanvasItemPrivate)
{
}

HCanvasItem::HCanvasItem(HCanvasItemPrivate &p) :
    d_ptr(&p)
{
}

HCanvasItem::~HCanvasItem()
{
}

double HCanvasItem::x() const
{
    return  d_ptr->x;
}

double HCanvasItem::y() const
{
    return  d_ptr->y;
}

double HCanvasItem::z() const
{
    return  d_ptr->z;
}

bool HCanvasItem::isAnimated() const
{
    return d_ptr->animated;
}

double HCanvasItem::xVelocity() const
{
    return d_ptr->extra != nullptr ? d_ptr->extra->vx : 0;
}

double HCanvasItem::yVelocity() const
{
    return d_ptr->extra != nullptr ? d_ptr->extra->vy : 0;
}

QList<HCanvasItem *> HCanvasItem::collisions(bool exact) const
{
    return canvas()->collisions(chunks(), this, exact);
}

void HCanvasItem::move(double x, double y)
{
    moveBy(x - d_ptr->x, y - d_ptr->y);
}

void HCanvasItem::setX(double value)
{
    move(value, y());
}

void HCanvasItem::setY(double value)
{
    move(x(), value);
}

void HCanvasItem::setZ(double value)
{
    d_ptr->z = value;
    changeChunks();
}

void HCanvasItem::setXVelocity(double value)
{
    setVelocity(value, yVelocity());
}

void HCanvasItem::setYVelocity(double value)
{
    setVelocity(xVelocity(), value);
}

void HCanvasItem::setCanvas(HCanvas *p)
{
    if (d_ptr->canvas == p)
        return;

    auto visible = isVisible();
    setVisible(false);
    if (d_ptr->canvas != nullptr)
    {
        if (d_ptr->extra)
            d_ptr->canvas->removeAnimation(this);
        d_ptr->canvas->removeItem(this);
    }
    d_ptr->canvas = p;
    if (d_ptr->canvas != nullptr)
    {
        d_ptr->canvas->addItem(this);
        if (d_ptr->extra)
            d_ptr->canvas->addAnimation(this);
    }
    setVisible(visible);
}

void HCanvasItem::setAnimated(bool b)
{
    if (d_ptr->animated == b)
        return;

    d_ptr->animated = b;
    if (b)
        d_ptr->canvas->addAnimation(this);
    else
        d_ptr->canvas->removeAnimation(this);
}

void HCanvasItem::setVelocity(double vx, double vy)
{
    if (d_ptr->extra || vx!= 0.0 || vy!= 0.0)
    {
        if (!d_ptr->animated)
            setAnimated(true);
        extra().vx = vx;
        extra().vy = vy;
    }
}

void HCanvasItem::moveBy(double dx, double dy)
{
    if (dx != 0 || dy != 0)
    {
        removeFromChunks();
        d_ptr->x += dx;
        d_ptr->y += dy;
        addToChunks();
    }
}

void HCanvasItem::advance(int stage)
{
    if (d_ptr->extra != nullptr && stage == 1)
        moveBy(d_ptr->extra->vx, d_ptr->extra->vy);
}



