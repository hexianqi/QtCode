#include "HBlindsEffect_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HBlindsEffect::HBlindsEffect(QObject *parent) :
    HAbstractShaderEffect(*new HBlindsEffectPrivate, parent)
{
}

HBlindsEffect::HBlindsEffect(HBlindsEffectPrivate &p, QObject *parent) :
    HAbstractShaderEffect(p, parent)
{
}

void HBlindsEffect::initialize(QVariantMap param)
{
    if (param.contains("page"))
        setPage(param.value("page").toInt());
    if (param.contains("direction"))
        setDirection(param.value("direction").value<HControlType::Direction4>());
}

QString HBlindsEffect::typeName()
{
    return "HBlindsEffect";
}

void HBlindsEffect::draw(QPainter *painter, double factor, const QRect &rect, const QPixmap &pixmap)
{
    Q_D(HBlindsEffect);
    auto x = (rect.width() - pixmap.width()) / 2;
    auto y = (rect.height() - pixmap.height()) / 2;
    auto s = ((d->direction == HControlType::Direction4_Down || d->direction == HControlType::Direction4_Up) ?  pixmap.height() : pixmap.width()) / d->page;
    auto wh = factor * s;
    if (wh < 1)
        return;
    painter->save();
    for(int i = 0; i < d->page; i++)
    {
        if (d->direction == HControlType::Direction4_Down)
            painter->drawPixmap(QPointF(x, y + i * s), pixmap, QRectF(0, i * s, pixmap.width(), wh));
        if (d->direction == HControlType::Direction4_Up)
            painter->drawPixmap(QPointF(x, y + i * s + s - wh), pixmap, QRectF(0, i * s + s - wh, pixmap.width(), wh));
        if (d->direction == HControlType::Direction4_Right)
            painter->drawPixmap(QPointF(x + i * s, y), pixmap, QRectF(i * s, 0, wh, pixmap.height()));
        if (d->direction == HControlType::Direction4_Left)
            painter->drawPixmap(QPointF(x + i * s + s - wh, y), pixmap, QRectF(i * s + s - wh, 0, wh, pixmap.height()));
    }
    painter->restore();
}

int HBlindsEffect::page() const
{
    Q_D(const HBlindsEffect);
    return d->page;
}

HControlType::Direction4 HBlindsEffect::direction() const
{
    Q_D(const HBlindsEffect);
    return d->direction;
}

void HBlindsEffect::setPage(int value)
{
    Q_D(HBlindsEffect);
    if (value < 2 || value > 100 || value == d->page)
        return;
    d->page = value;
}

void HBlindsEffect::setDirection(HControlType::Direction4 value)
{
    Q_D(HBlindsEffect);
    if (value == d->direction)
        return;
    d->direction = value;
}

HE_CONTROL_END_NAMESPACE
