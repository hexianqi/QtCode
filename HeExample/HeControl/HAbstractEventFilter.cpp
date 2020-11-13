#include "HAbstractEventFilter_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HAbstractEventFilter::HAbstractEventFilter(QObject *parent) :
    IEventFilter(parent),
    d_ptr(new HAbstractEventFilterPrivate)
{
}

HAbstractEventFilter::HAbstractEventFilter(HAbstractEventFilterPrivate &p, QObject *parent) :
    IEventFilter(parent),
    d_ptr(&p)
{
}

HAbstractEventFilter::~HAbstractEventFilter() = default;

bool HAbstractEventFilter::setEnable(bool b)
{
    if (d_ptr->enable == b)
        return false;
    d_ptr->enable = b;
    return true;
}

bool HAbstractEventFilter::isEnable()
{
    return d_ptr->enable;
}

bool HAbstractEventFilter::addWatched(QObject *p)
{
    if (hasWatched(p))
        return false;
    d_ptr->watcheds.insert(p);
    p->installEventFilter(this);
    return true;
}

void HAbstractEventFilter::addHandler(QEvent::Type type, std::function<bool (QEvent *)> func)
{
    d_ptr->handlers.insert(type, func);
}

bool HAbstractEventFilter::eventFilter(QObject *watched, QEvent *event)
{
    if (!isEnable())
        return false;
    if (!hasWatched(watched))
        return false;
    if (handleEvent(watched, event))
        return true;
    if (hasHandler(event->type()))
        return d_ptr->handlers.value(event->type())(event);
    return QObject::eventFilter(watched, event);
}

bool HAbstractEventFilter::hasWatched(QObject *p)
{
    return d_ptr->watcheds.contains(p);
}

bool HAbstractEventFilter::hasHandler(QEvent::Type t)
{
    return d_ptr->handlers.contains(t);
}

HE_CONTROL_END_NAMESPACE
