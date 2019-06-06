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
    d->isPressed = true;
    d->pos = e->pos();
    return true;
}

bool HMoveEventFilter::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(HMoveEventFilter);
    if (e->button() != Qt::LeftButton)
        return false;
    d->isPressed = false;
    return true;
}

bool HMoveEventFilter::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HMoveEventFilter);
    if (!d->isPressed)
        return false;
    d->parent->move(e->globalPos() - d->pos);
    return true;
}

HE_CONTROL_END_NAMESPACE
