#include "HPositionTracking_p.h"
#include <QMouseEvent>

HPositionTracking::HPositionTracking(QWidget *parent)
    : QLabel(parent), d_ptr(new HPositionTrackingPrivate)
{
    setAlignment(Qt::AlignLeft | Qt::AlignBottom);
}

HPositionTracking::~HPositionTracking()
{
}

void HPositionTracking::setValidRegion(QRectF value)
{
    d_ptr->validRegion = value;
    auto h = fontMetrics().height();
    setGeometry(value.left() + 10, value.top() + 10, value.width() - 20, h);
}

void HPositionTracking::setEnableTracking(bool b)
{
    d_ptr->enableTracking = b;
    setVisible(b);
}

bool HPositionTracking::isEnableTracking()
{
    return d_ptr->enableTracking;
}

void HPositionTracking::mouseMoveEvent(QMouseEvent *e)
{
    if(isEnableTracking() && d_ptr->validRegion.contains(e->pos()))
        emit positionChanged(e->pos());
}
