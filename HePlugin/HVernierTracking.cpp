#include "HVernierTracking_p.h"
#include <QStylePainter>

HVernierTrackingPrivate::HVernierTrackingPrivate()
{
    pos = -1;
    enableTracking = true;
    color = Qt::blue;
    validRegion.setRect(0, 0, 1, 1);
}

void HVernierTrackingPrivate::setValidRegion(QRectF value)
{
    auto dx = value.width() / validRegion.width();
    auto dy = value.height() / validRegion.height();
    for (int i = 0; i < verniers.count(); i++)
    {
        auto x = value.left() + (verniers[i].x() - validRegion.left()) * dx;
        auto y = value.top() + (verniers[i].y() - validRegion.top()) * dy;
        x = qBound(value.left(), x, value.right());
        y = qBound(value.top(), y, value.bottom());
        verniers[i] = QPointF(x, y);
    }
    validRegion = value;
}

void HVernierTrackingPrivate::setVernier(int size)
{
    verniers.reserve(size);
    if (size < 1)
        return;

    verniers[0] = validRegion.topLeft();
    for (int i = 1; i < size; i++)
        setVernier(i, i / (size - 1));
}

void HVernierTrackingPrivate::setVernier(int i, double percent)
{
    if (i < 0 || i >= verniers.size())
        return;

    percent = qBound(0.0, percent, 1.0);
    verniers[i].rx() = validRegion.left() + validRegion.width() * percent;
    verniers[i].ry() = validRegion.top() + validRegion.height() * percent;
}

void HVernierTrackingPrivate::paintVernier(QStylePainter *p)
{
    p->save();
    p->setPen(color);
    for (auto v : verniers)
    {
        if (orientation == Qt::Horizontal)
            p->drawLine(validRegion.left() + 2, v.y(), validRegion.right() - 2, v.y());
        if (orientation == Qt::Vertical)
            p->drawLine(v.x(), validRegion.top() + 2, v.x(), validRegion.bottom() - 2);
    }
    p->restore();
}

HVernierTracking::HVernierTracking(Qt::Orientation orientation, QWidget *parent)
    : QWidget(parent), d_ptr(new HVernierTrackingPrivate)
{
    d_ptr->orientation = orientation;
}

HVernierTracking::~HVernierTracking()
{
}

void HVernierTracking::setValidRegion(QRectF value)
{
    d_ptr->setValidRegion(value);
}

void HVernierTracking::setEnableTracking(bool b)
{
    d_ptr->enableTracking = b;
}

void HVernierTracking::setVernierColor(QColor value)
{
    d_ptr->color = value;
}

void HVernierTracking::setVernier(int size)
{
    d_ptr->setVernier(size);
    emit vernierChanged();
}

void HVernierTracking::setVernier(int i, double percent)
{
    d_ptr->setVernier(i, percent);
    emit vernierChanged(d_ptr->verniers[i]);
}

bool HVernierTracking::isEnableTracking()
{
    return d_ptr->enableTracking;
}

void HVernierTracking::paintEvent(QPaintEvent *)
{
    d_ptr->paintVernier(new QStylePainter(this));
}

void HVernierTracking::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        for (int i = 0; i < d_ptr->verniers.size(); i++)
        {
            if (d_ptr->orientation == Qt::Horizontal && qAbs(e->y() - m_ptVerniers[i].y()) < 5)
            {
                d_ptr->pos = i;
                setCursor(Qt::SizeVerCursor);
                break;
            }
            if (d_ptr->orientation == Qt::Vertical && qAbs(e->x() - m_ptVerniers[i].x()) < 5)
            {
                m_nPos = i;
                m_bTracking = true;
                m_pWidget->setCursor(Qt::SizeHorCursor);
                break;
            }
        }
    }
    QWidget::mousePressEvent(e);
}

void HVernierTracking::mouseMoveEvent(QMouseEvent *)
{

}

void HVernierTracking::mouseReleaseEvent(QMouseEvent *)
{

}


