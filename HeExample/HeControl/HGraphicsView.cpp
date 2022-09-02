#include "HGraphicsView_p.h"
#include <QtGui/QtEvents>

HE_BEGIN_NAMESPACE

HGraphicsView::HGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    d_ptr(new HGraphicsViewPrivate)
{
    setMouseTracking(true);
}

HGraphicsView::HGraphicsView(HGraphicsViewPrivate &p, QWidget *parent) :
    QGraphicsView(parent),
    d_ptr(&p)
{
    setMouseTracking(true);
}

HGraphicsView::~HGraphicsView()
{
}

void HGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMovePos(event->localPos());
    return QGraphicsView::mouseMoveEvent(event);
}

HE_END_NAMESPACE
