#include "HRubberBand_p.h"
#include <QtGui/QMouseEvent>
#include <QtWidgets/QRubberBand>

HRubberBandPrivate::HRubberBandPrivate(QWidget *p) :
    HAbstractMouseStrategyPrivate(p)
{
    rubberBand = new QRubberBand(QRubberBand::Rectangle, p);
}

HRubberBand::HRubberBand(QWidget *parent) :
    HAbstractMouseStrategy(*new HRubberBandPrivate(parent), parent)
{
}

HRubberBand::HRubberBand(HRubberBandPrivate &p, QWidget *parent) :
    HAbstractMouseStrategy(p, parent)
{
}

bool HRubberBand::setEnable(bool b)
{
    Q_D(HRubberBand);
    if (!HAbstractMouseStrategy::setEnable(b))
        return false;
    d->rubberBand->setEnabled(b);
    return true;
}

bool HRubberBand::mousePressEvent(QMouseEvent *e)
{
    Q_D(HRubberBand);
    if (!isValid(e->localPos()) || e->button() != Qt::LeftButton)
        return false;
    d->origin = e->pos();
    d->rubberBand->setGeometry(QRect(e->pos(), QSize()));
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
    auto rect = d->validRegion.intersected(d->rubberBand->geometry()).normalized();
    if (rect.width() < 4 || rect.height() < 4)
        return false;
    emit rubberBandChanged(rect);
    return true;
}
