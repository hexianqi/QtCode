#include "HAbstractMouseEventFilter_p.h"
#include <QtGui/QMouseEvent>
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

HAbstractMouseEventFilterPrivate::HAbstractMouseEventFilterPrivate(QWidget *p)
{
    parent = p;
}

HAbstractMouseEventFilter::HAbstractMouseEventFilter(QWidget *parent) :
    HAbstractEventFilter(*new HAbstractMouseEventFilterPrivate(parent), parent)
{
}

HAbstractMouseEventFilter::HAbstractMouseEventFilter(HAbstractMouseEventFilterPrivate &p, QWidget *parent) :
    HAbstractEventFilter(p, parent)
{
}

HAbstractMouseEventFilter::~HAbstractMouseEventFilter()
{
}

bool HAbstractMouseEventFilter::eventFilter(QObject *watched, QEvent *event)
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
    return HAbstractEventFilter::eventFilter(watched, event);
}

bool HAbstractMouseEventFilter::isValid(QPointF pos)
{
    return d_ptr->validRegion.contains(pos);
}

HE_CONTROL_END_NAMESPACE
