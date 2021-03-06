#include "HMoveEventFilter_p.h"
#include <QtGui/QMouseEvent>
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

HMoveEventFilter::HMoveEventFilter(QWidget *parent) :
    HAbstractMouseEventFilter(*new HMoveEventFilterPrivate(parent), parent)
{
}

HMoveEventFilter::~HMoveEventFilter()
{
}

bool HMoveEventFilter::mousePressEvent(QMouseEvent *e)
{
    Q_D(HMoveEventFilter);
    if (e->button() != Qt::LeftButton)
        return false;
    d->pressed = true;
    d->pos = e->pos();
    d->parent->setCursor(Qt::OpenHandCursor);
    return true;
}

bool HMoveEventFilter::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(HMoveEventFilter);
    if (e->button() != Qt::LeftButton)
        return false;
    d->pressed = false;
    d->parent->setCursor(Qt::ArrowCursor);
    return true;
}

bool HMoveEventFilter::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HMoveEventFilter);
    if (!d->pressed)
        return false;
    d->parent->move(e->globalPos() - d->pos);
    return true;
}

HE_CONTROL_END_NAMESPACE
