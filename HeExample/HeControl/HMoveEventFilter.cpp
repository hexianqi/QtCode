#include "HMoveEventFilter_p.h"
#include <QtGui/QMouseEvent>
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

HMoveEventFilter::HMoveEventFilter(QObject *parent) :
    HAbstractMouseEventFilter(*new HMoveEventFilterPrivate, parent)
{
}

QString HMoveEventFilter::typeName()
{
    return "HMoveEventFilter";
}

bool HMoveEventFilter::handleMousePressEvent(QWidget *widget, QMouseEvent *event)
{
    Q_D(HMoveEventFilter);
    if (event->button() != Qt::LeftButton)
        return false;
    if (!widget->rect().contains(event->pos()))
        return false;
    d->pressed = true;
    d->lastPos = event->pos();
    widget->setCursor(Qt::OpenHandCursor);
    return true;
}

bool HMoveEventFilter::handleMouseReleaseEvent(QWidget *widget, QMouseEvent *event)
{
    Q_D(HMoveEventFilter);
    if (event->button() != Qt::LeftButton || !d->pressed)
        return false;
    d->pressed = false;
    widget->setCursor(Qt::ArrowCursor);
    return true;
}

bool HMoveEventFilter::handleMouseMoveEvent(QWidget *widget, QMouseEvent *event)
{
    Q_D(HMoveEventFilter);
    if (!d->pressed)
        return false;
    widget->move(widget->pos() + event->pos() - d->lastPos);
    return true;
}

HE_END_NAMESPACE
