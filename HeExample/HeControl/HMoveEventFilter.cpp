#include "HMoveEventFilter_p.h"
#include <QtGui/QMouseEvent>
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

HMoveEventFilter::HMoveEventFilter(QObject *parent) :
    HAbstractMouseEventFilter(*new HMoveEventFilterPrivate, parent)
{
}

HMoveEventFilter::~HMoveEventFilter()
{
}

void HMoveEventFilter::initialize(QVariantMap /*param*/)
{

}

QString HMoveEventFilter::typeName()
{
    return "HMoveEventFilter";
}

bool HMoveEventFilter::mousePressEvent(QWidget *widget, QMouseEvent *event)
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

bool HMoveEventFilter::mouseReleaseEvent(QWidget *widget, QMouseEvent *event)
{
    Q_D(HMoveEventFilter);
    if (event->button() != Qt::LeftButton || !d->pressed)
        return false;
    d->pressed = false;
    widget->setCursor(Qt::ArrowCursor);
    return true;
}

bool HMoveEventFilter::mouseMoveEvent(QWidget *widget, QMouseEvent *event)
{
    Q_D(HMoveEventFilter);
    if (!d->pressed)
        return false;
    widget->move(event->globalPos() - d->lastPos);
    return true;
}

HE_CONTROL_END_NAMESPACE
