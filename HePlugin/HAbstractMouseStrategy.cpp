#include "HAbstractMouseStrategy_p.h"
#include <QWidget>

HAbstractMouseStrategyPrivate::HAbstractMouseStrategyPrivate(QWidget *p)
    : parent(p)
{
}

bool HAbstractMouseStrategyPrivate::isValid(QPointF pos)
{
    return enable && validRegion.contains(pos);
}

HAbstractMouseStrategy::HAbstractMouseStrategy(QWidget *parent)
    : QObject(parent), d_ptr(new HAbstractMouseStrategyPrivate(parent))
{
}

HAbstractMouseStrategy::HAbstractMouseStrategy(HAbstractMouseStrategyPrivate &p, QWidget *parent)
    : QObject(parent), d_ptr(&p)
{
}

HAbstractMouseStrategy::~HAbstractMouseStrategy()
{
}

void HAbstractMouseStrategy::setValidRegion(QRectF value)
{
    d_ptr->validRegion = value;
}

void HAbstractMouseStrategy::setEnable(bool b)
{
    d_ptr->enable = b;
}

bool HAbstractMouseStrategy::isEnable()
{
    return d_ptr->enable;
}
