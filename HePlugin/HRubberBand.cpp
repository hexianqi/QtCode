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
    auto rect = d->validRegion.intersected(d->rubberBand->geometry());
    rect = rect.normalized();
    if (rect.width() < 4 || rect.height() < 4)
        return false;
    emit rubberBandChanged(rect);
    return true;
}
