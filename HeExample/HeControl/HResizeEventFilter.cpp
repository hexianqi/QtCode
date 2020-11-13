#include "HResizeEventFilter_p.h"
#include <QtGui/QMouseEvent>
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

HResizeEventFilter::HResizeEventFilter(QObject *parent) :
    HAbstractMouseEventFilter(*new HResizeEventFilterPrivate, parent)
{
}

HResizeEventFilter::HResizeEventFilter(HResizeEventFilterPrivate &p, QObject *parent) :
    HAbstractMouseEventFilter(p, parent)
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
    if (!HAbstractMouseEventFilter::addWatched(p))
        return false;
    auto w = qobject_cast<QWidget *>(p);
    w->setAttribute(Qt::WA_Hover, true);
    return true;
}

bool HResizeEventFilter::handleEvent(QObject *watched, QEvent *event)
{
    auto w = qobject_cast<QWidget *>(watched);
    if (w == nullptr)
        return false;
    if (event->type() == QEvent::Resize)
        return handleResizeEvent(w, event);
    if (event->type() == QEvent::HoverMove)
        return handleHoverMoveEvent(w, event);
    return HAbstractMouseEventFilter::handleEvent(watched, event);
}

bool HResizeEventFilter::handleMousePressEvent(QWidget *widget, QMouseEvent *event)
{
    Q_D(HResizeEventFilter);
    if (event->button() != Qt::LeftButton)
        return false;
    auto pos = event->pos();
    if (d->rectLeft.contains(pos))
        d->pressedLeft = true;
    else if (d->rectRight.contains(pos))
        d->pressedRight = true;
    else if (d->rectTop.contains(pos))
        d->pressedTop = true;
    else if (d->rectBottom.contains(pos))
        d->pressedBottom = true;
    else if (d->rectTopLeft.contains(pos))
        d->pressedTopLeft = true;
    else if (d->rectTopRight.contains(pos))
        d->pressedTopRight = true;
    else if (d->rectBottomLeft.contains(pos))
        d->pressedBottomLeft = true;
    else if (d->rectBottomRight.contains(pos))
        d->pressedBottomRight = true;
    else
        return false;
    d->pressed = true;
    d->lastPos = pos;
    d->lastGeometry = widget->geometry();
    return true;
}

bool HResizeEventFilter::handleMouseReleaseEvent(QWidget *widget, QMouseEvent *event)
{
    Q_D(HResizeEventFilter);
    if (event->button() != Qt::LeftButton || !d->pressed)
        return false;
    d->pressed = false;
    d->pressedLeft = false;
    d->pressedRight = false;
    d->pressedTop = false;
    d->pressedBottom = false;
    d->pressedTopLeft = false;
    d->pressedTopRight = false;
    d->pressedBottomLeft = false;
    d->pressedBottomRight = false;
    widget->setCursor(Qt::ArrowCursor);
    return true;
}

bool HResizeEventFilter::handleMouseMoveEvent(QWidget *, QMouseEvent *)
{
    return false;
}

bool HResizeEventFilter::handleResizeEvent(QWidget *widget, QEvent *)
{
    Q_D(HResizeEventFilter);
    auto width = widget->width();
    auto height = widget->height();
    d->rectLeft = QRect(0, d->padding, d->padding, height - d->padding * 2);
    d->rectTop = QRect(d->padding, 0, width - d->padding * 2, d->padding);
    d->rectRight = QRect(width - d->padding, d->padding, d->padding, height - d->padding * 2);
    d->rectBottom = QRect(d->padding, height - d->padding, width - d->padding * 2, d->padding);
    d->rectTopLeft = QRect(0, 0, d->padding, d->padding);
    d->rectTopRight = QRect(width - d->padding, 0, d->padding, d->padding);
    d->rectBottomLeft = QRect(0, height - d->padding, d->padding, d->padding);
    d->rectBottomRight = QRect(width - d->padding, height - d->padding, d->padding, d->padding);
    return false;
}

bool HResizeEventFilter::handleHoverMoveEvent(QWidget *widget, QEvent *event)
{
    Q_D(HResizeEventFilter);
    auto e = dynamic_cast<QHoverEvent *>(event);
    auto pos = e->pos();
    auto offsetX = pos.x() - d->lastPos.x();
    auto offsetY = pos.y() - d->lastPos.y();
    if (d->rectLeft.contains(pos))
        widget->setCursor(Qt::SizeHorCursor);
    else if (d->rectRight.contains(pos))
        widget->setCursor(Qt::SizeHorCursor);
    else if (d->rectTop.contains(pos))
        widget->setCursor(Qt::SizeVerCursor);
    else if (d->rectBottom.contains(pos))
        widget->setCursor(Qt::SizeVerCursor);
    else if (d->rectTopLeft.contains(pos))
        widget->setCursor(Qt::SizeFDiagCursor);
    else if (d->rectTopRight.contains(pos))
        widget->setCursor(Qt::SizeBDiagCursor);
    else if (d->rectBottomLeft.contains(pos))
        widget->setCursor(Qt::SizeBDiagCursor);
    else if (d->rectBottomRight.contains(pos))
        widget->setCursor(Qt::SizeFDiagCursor);
    else
        widget->setCursor(Qt::ArrowCursor);

    if (d->pressedLeft)
    {
        auto resizeW = widget->width() - offsetX;
        if (widget->minimumWidth() <= resizeW && widget->maximumWidth() >= resizeW)
            widget->setGeometry(widget->x() + offsetX, d->lastGeometry.top(), resizeW, d->lastGeometry.height());
    }
    else if (d->pressedRight)
    {
        auto resizeW = widget->width() + offsetX;
        if (widget->minimumWidth() <= resizeW && widget->maximumWidth() >= resizeW)
            widget->setGeometry(d->lastGeometry.adjusted(0, 0, offsetX, 0));
    }
    else if (d->pressedTop)
    {
        auto resizeH = widget->height() - offsetY;
        if (widget->minimumHeight() <= resizeH && widget->maximumHeight() >= resizeH)
            widget->setGeometry(d->lastGeometry.left(), widget->y() + offsetY, d->lastGeometry.width(), resizeH);
    }
    else if (d->pressedBottom)
    {
        auto resizeH = widget->height() + offsetY;
        if (widget->minimumHeight() <= resizeH && widget->maximumHeight() >= resizeH)
            widget->setGeometry(d->lastGeometry.adjusted(0, 0, 0, offsetY));
    }
    else if (d->pressedTopLeft)
    {
        auto resizeW = widget->width() - offsetX;
        auto resizeH = widget->height() - offsetY;
        if (widget->minimumWidth() <= resizeW && widget->maximumWidth() >= resizeW)
            widget->setGeometry(widget->x() + offsetX, widget->y(), resizeW, resizeH);
        if (widget->minimumHeight() <= resizeH && widget->maximumHeight() >= resizeH)
            widget->setGeometry(widget->x(), widget->y() + offsetY, resizeW, resizeH);
    }
    else if (d->pressedTopRight)
    {
        auto resizeW = d->lastGeometry.width() + offsetX;
        auto resizeH = widget->height() - offsetY;
        if (widget->minimumWidth() <= resizeW && widget->maximumWidth() >= resizeW && widget->minimumHeight() <= resizeH && widget->maximumHeight() >= resizeH)
            widget->setGeometry(widget->x(), widget->y() + offsetY, resizeW, resizeH);
    }
    else if (d->pressedBottomLeft)
    {
        auto resizeW = widget->width() - offsetX;
        auto resizeH = d->lastGeometry.height() + offsetY;
        if (widget->minimumWidth() <= resizeW && widget->maximumWidth() >= resizeW)
            widget->setGeometry(widget->x() + offsetX, widget->y(), resizeW, resizeH);
        if (widget->minimumHeight() <= resizeH && widget->maximumHeight() >= resizeH)
            widget->setGeometry(widget->x(), widget->y(), resizeW, resizeH);
    }
    else if (d->pressedBottomRight)
    {
        auto resizeW = d->lastGeometry.width() + offsetX;
        auto resizeH = d->lastGeometry.height() + offsetY;
        if (widget->minimumWidth() <= resizeW && widget->maximumWidth() >= resizeW && widget->minimumHeight() <= resizeH && widget->maximumHeight() >= resizeH)
            widget->setGeometry(widget->x(), widget->y(), resizeW, resizeH);
    }
    return true;
}

HE_CONTROL_END_NAMESPACE
