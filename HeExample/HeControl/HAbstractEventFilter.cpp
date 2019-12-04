#include "HAbstractEventFilter_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HAbstractEventFilter::HAbstractEventFilter(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractEventFilterPrivate)
{
}

HAbstractEventFilter::HAbstractEventFilter(HAbstractEventFilterPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractEventFilter::~HAbstractEventFilter()
{
}

bool HAbstractEventFilter::setValidRegion(QRectF value)
{
    if (d_ptr->validRegion == value)
        return false;
    d_ptr->validRegion = value;
    return true;
}

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

void HAbstractEventFilter::addHandle(QEvent::Type type, std::function<bool (QEvent *)> func)
{
    d_ptr->handleFunc.insert(type, func);
}

bool HAbstractEventFilter::eventFilter(QObject */*watched*/, QEvent *event)
{
    if (!isEnable() || !d_ptr->handleFunc.contains(event->type()))
        return false;
    return d_ptr->handleFunc.value(event->type())(event);
}

HE_CONTROL_END_NAMESPACE
