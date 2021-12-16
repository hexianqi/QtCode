#include "HProp_p.h"

HE_BEGIN_NAMESPACE

HProp::HProp(QObject *parent) :
    HGameObject(*new HPropPrivate, parent)
{
}

HProp::HProp(HPropPrivate &p, QObject *parent) :
    HGameObject(p, parent)
{
}

HProp::~HProp()
{
}

QString HProp::type()
{
    Q_D(HProp);
    return d->type;
}

bool HProp::isActivated()
{
    Q_D(HProp);
    return d->activated;
}

bool HProp::isDestroyed()
{
    Q_D(HProp);
    return d->destroyed;
}

bool HProp::isPermanent()
{
    Q_D(HProp);
    return d->type == "speed" || d->type == "increase";
}

void HProp::setType(const QString &value)
{
    Q_D(HProp);
    d->type = value;
}

void HProp::setDuration(float value)
{
    Q_D(HProp);
    d->duration = value;
}

void HProp::setActivated(bool b)
{
    Q_D(HProp);
    if (d->activated == b)
        return;
    d->activated = b;
    emit activateChanged(b);
}

void HProp::setDestroyed(bool b)
{
    Q_D(HProp);
    d->destroyed = b;
}

void HProp::update(float dt)
{
    Q_D(HProp);
    d->position += d->velocity * dt;
    if (!d->activated || isPermanent())
        return;
    d->duration -= dt;
    if (d->duration > 0.0f)
        return;
    setActivated(false);
}

HE_END_NAMESPACE
