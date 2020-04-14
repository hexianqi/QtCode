#include "HAbstractMouseStrategy_p.h"
#include <QtWidgets/QWidget>

HAbstractMouseStrategyPrivate::HAbstractMouseStrategyPrivate(QWidget *p) :
    parent(p)
{
}

HAbstractMouseStrategy::HAbstractMouseStrategy(QWidget *parent) :
    QObject(parent),
    d_ptr(new HAbstractMouseStrategyPrivate(parent))
{
}

HAbstractMouseStrategy::~HAbstractMouseStrategy() = default;

HAbstractMouseStrategy::HAbstractMouseStrategy(HAbstractMouseStrategyPrivate &p, QWidget *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

bool HAbstractMouseStrategy::setValidRegion(QRectF value)
{
    if (d_ptr->validRegion == value)
        return false;
    d_ptr->validRegion = value;
    return true;
}

bool HAbstractMouseStrategy::setEnable(bool b)
{
    if (d_ptr->enable == b)
        return false;
    d_ptr->enable = b;
    return true;
}

bool HAbstractMouseStrategy::isEnable()
{
    return d_ptr->enable;
}

bool HAbstractMouseStrategy::isValid(QPointF pos)
{
    return isEnable() && d_ptr->validRegion.contains(pos);
}
