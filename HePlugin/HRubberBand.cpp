#include "HRubberBand_p.h"
#include "HAbstractDomain.h"
#include <QRubberBand>
#include <QMouseEvent>

HRubberBandPrivate::HRubberBandPrivate(QWidget *p)
    : HAbstractMouseStrategyPrivate(p)
{
    rubberBand = new QRubberBand(QRubberBand::Rectangle, p);
}

HRubberBand::HRubberBand(QWidget *parent)
    : HAbstractMouseStrategy(*new HRubberBandPrivate(parent), parent)
{
}

HRubberBand::HRubberBand(HRubberBandPrivate &p, QWidget *parent)
    : HAbstractMouseStrategy(p, parent)
{
}

HRubberBand::~HRubberBand()
{
}

void HRubberBand::setEnable(bool b)
{
    Q_D(HRubberBand);
    d->rubberBand->setEnabled(b);
    HAbstractMouseStrategy::setEnable(b);
}

void HRubberBand::paintEvent(QStylePainter *)
{
}

bool HRubberBand::mousePressEvent(QMouseEvent *e)
{
    Q_D(HRubberBand);
    if (!d->isValid(e->localPos()) || e->button() != Qt::LeftButton)
        return false;

    d->origin = e->pos();
    d->rubberBand->setGeometry(QRect(d->origin, QSize()));
    d->rubberBand->show();
    return true;
}

bool HRubberBand::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HRubberBand);
    if (!isEnable() || !d->rubberBand->isVisible())
        return false;
    d->rubberBand->setGeometry(QRect(d->origin, e->pos()).normalized());
    return true;
}

bool HRubberBand::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(HRubberBand);
    if (!isEnable() || !d->rubberBand->isVisible() || e->button() != Qt::LeftButton)
        return false;

    d->rubberBand->hide();
    auto validRegion = d->validRegion;
    auto geometry = d->rubberBand->geometry();
    QRectF rect;
    rect.setLeft(qBound(validRegion.left(), 1.0 * geometry.left(), validRegion.right()));
    rect.setRight(qBound(validRegion.left(), 1.0 * geometry.right(), validRegion.right()));
    rect.setTop(qBound(validRegion.top(), 1.0 * geometry.top(), validRegion.bottom()));
    rect.setBottom(qBound(validRegion.top(), 1.0 * geometry.bottom(), validRegion.bottom()));
    rect = rect.normalized();
    if (rect.width() < 4 || rect.height() < 4)
        return false;
    emit rubberBandChanged(rect);
    return true;
}
