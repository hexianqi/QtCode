#include "HResizeEventFilter_p.h"
#include <QtGui/QMouseEvent>
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

HResizeEventFilter::HResizeEventFilter(QObject *parent) :
    HAbstractEventFilter(*new HResizeEventFilterPrivate, parent)
{
}

HResizeEventFilter::HResizeEventFilter(HResizeEventFilterPrivate &p, QObject *parent) :
    HAbstractEventFilter(p, parent)
{
}

HResizeEventFilter::~HResizeEventFilter()
{
}

void HResizeEventFilter::initialize(QVariantMap /*param*/)
{

}

QString HResizeEventFilter::typeName()
{
    return "HResizeEventFilter";
}

bool HResizeEventFilter::addWatched(QObject *p)
{
    if (!p->inherits("QWidget"))
        return false;
    return HAbstractEventFilter::addWatched(p);
}

bool HResizeEventFilter::handleInternal(QObject *watched, QEvent *event)
{
    auto w = static_cast<QWidget *>(watched);
    if (w == nullptr)
        return false;
    if (event->type() == QEvent::Resize)
        return resizeEvent(w, event);
    auto e = static_cast<QMouseEvent *>(event);
    if (e == nullptr)
        return false;
    if (e->type() == QEvent::MouseButtonPress)
        return mousePressEvent(w, e);
    if (e->type() == QEvent::MouseButtonRelease)
        return mouseReleaseEvent(w, e);
    if (e->type() == QEvent::HoverMove)
        return hoverMoveEvent(w, e);
    return false;
}

bool HResizeEventFilter::resizeEvent(QWidget *widget, QEvent *)
{
    Q_D(HResizeEventFilter);
    auto width = widget->width();
    auto height = widget->height();
    d->rectLeft = QRect(0, d->padding, d->padding, height - d->padding * 2);
    d->rectTop = QRect(d->padding, 0, width - d->padding * 2, d->padding);
    d->rectRight = QRect(width - d->padding, d->padding, d->padding, height - d->padding * 2);
    d->rectBottom = QRect(d->padding, height - d->padding, width - d->padding * 2, d->padding);
    d->rectLeftTop = QRect(0, 0, d->padding, d->padding);
    d->rectRightTop = QRect(width - d->padding, 0, d->padding, d->padding);
    d->rectLeftBottom = QRect(0, height - d->padding, d->padding, d->padding);
    d->rectRightBottom = QRect(width - d->padding, height - d->padding, d->padding, d->padding);
    return false;
}

bool HResizeEventFilter::mousePressEvent(QWidget *widget, QMouseEvent *event)
{
    Q_D(HResizeEventFilter);
    if (event->button() != Qt::LeftButton)
        return false;
    d->preRect = widget->rect();
    auto pos = event->pos();
    if (d->rectLeft.contains(pos))
        d->pressedLeft = true;
    else if (d->rectRight.contains(pos))
        d->pressedRight = true;
    else if (d->rectTop.contains(pos))
        d->pressedTop = true;
    else if (d->rectBottom.contains(pos))
        d->pressedBottom = true;
    else if (d->rectLeftTop.contains(pos))
        d->pressedLeftTop = true;
    else if (d->rectRightTop.contains(pos))
        d->pressedRightTop = true;
    else if (d->rectLeftBottom.contains(pos))
        d->pressedLeftBottom = true;
    else if (d->rectRightBottom.contains(pos))
        d->pressedRightBottom = true;
    return true;
}

HE_CONTROL_END_NAMESPACE
