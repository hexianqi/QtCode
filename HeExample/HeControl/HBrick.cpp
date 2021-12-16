#include "HBrick_p.h"

HE_BEGIN_NAMESPACE

HBrick::HBrick(QObject *parent) :
    HGameObject(*new HBrickPrivate, parent)
{
}

HBrick::HBrick(HBrickPrivate &p, QObject *parent) :
    HGameObject(p, parent)
{
}

HBrick::~HBrick() = default;

bool HBrick::isSolid()
{
    Q_D(HBrick);
    return d->solid;
}

bool HBrick::isDestroyed()
{
    Q_D(HBrick);
    return d->destroyed;
}

void HBrick::setSolid(bool b)
{
    Q_D(HBrick);
    d->solid = b;
}

void HBrick::setDestroyed(bool b)
{
    Q_D(HBrick);
    d->destroyed = b;
}

HE_END_NAMESPACE
