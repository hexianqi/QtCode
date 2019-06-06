#include "HAbstractMouseEventFilter_p.h"
#include <QtGui/QMouseEvent>
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

HAbstractMouseEventFilterPrivate::HAbstractMouseEventFilterPrivate(QWidget *p)
{
    parent = p;
}

HAbstractMouseEventFilter::HAbstractMouseEventFilter(QWidget *parent) :
    QObject(parent),
    d_ptr(new HAbstractMouseEventFilterPrivate(parent))
{
}

HAbstractMouseEventFilter::HAbstractMouseEventFilter(HAbstractMouseEventFilterPrivate &p, QWidget *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractMouseEventFilter::~HAbstractMouseEventFilter()
{
}

bool HAbstractMouseEventFilter::setValidRegion(QRectF value)
{
    if (d_ptr->validRegion == value)
        return false;
    d_ptr->validRegion = value;
    return true;
}

bool HAbstractMouseEventFilter::setEnable(bool b)
{
    if (d_ptr->enable == b)
        return false;
    d_ptr->enable = b;
    return true;
}

bool HAbstractMouseEventFilter::isEnable()
{
    return d_ptr->enable;
}

bool HAbstractMouseEventFilter::eventFilter(QObject */*watched*/, QEvent *event)
{
    if (!isEnable())
        return false;
    auto e = static_cast<QMouseEvent *>(event);
    if (e == nullptr)
        return false;
    if (e->type() == QEvent::MouseButtonPress)
        return mousePressEvent(e);
    if (e->type() == QEvent::MouseButtonRelease)
        return mouseReleaseEvent(e);
    if (e->type() == QEvent::MouseMove)
        return mouseMoveEvent(e);
    return false;
}

bool HAbstractMouseEventFilter::isValid(QPointF pos)
{
    return d_ptr->validRegion.contains(pos);
}

HE_CONTROL_END_NAMESPACE
