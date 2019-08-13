#include "HMoveEffect_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HMoveEffect::HMoveEffect(QObject *parent) :
    HAbstractShaderEffect(*new HMoveEffectPrivate, parent)
{
}

HMoveEffect::HMoveEffect(HMoveEffectPrivate &p, QObject *parent) :
    HAbstractShaderEffect(p, parent)
{
}

HMoveEffect::~HMoveEffect()
{
}

void HMoveEffect::initialize(QVariantMap param)
{
    if (param.contains("direction"))
        setDirection(param.value("direction").value<HControlType::Direction4>());
}

QString HMoveEffect::typeName()
{
    return "HMoveEffect";
}

void HMoveEffect::draw(QPainter *painter, double factor, const QRect &rect, const QPixmap &pixmap)
{
    Q_D(HMoveEffect);
    auto w = rect.width();
    auto h = rect.height();
    auto x = (w - pixmap.width()) / 2.0;
    auto y = (h - pixmap.height()) / 2.0;

    d->direction = HControlType::Direction4_Down;
    if (d->direction == HControlType::Direction4_Left)
        x = x + w * (1 - factor);
    if (d->direction == HControlType::Direction4_Right)
        x = x + w * (factor - 1);
    if (d->direction == HControlType::Direction4_Up)
        y = y + h * (1 - factor);
    if (d->direction == HControlType::Direction4_Down)
        y = y + h * (factor - 1);

    painter->save();
    painter->drawPixmap(QPointF(x, y), pixmap);
    painter->restore();
}

HControlType::Direction4 HMoveEffect::direction() const
{
    Q_D(const HMoveEffect);
    return d->direction;
}

void HMoveEffect::setDirection(HControlType::Direction4 value)
{
    Q_D(HMoveEffect);
    if (value == d->direction)
        return;
    d->direction = value;
}

HE_CONTROL_END_NAMESPACE
