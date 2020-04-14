#include "HFlipEffect_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HFlipEffect::HFlipEffect(QObject *parent) :
    HAbstractShaderEffect(*new HFlipEffectPrivate, parent)
{
}

HFlipEffect::HFlipEffect(HFlipEffectPrivate &p, QObject *parent) :
    HAbstractShaderEffect(p, parent)
{
}

void HFlipEffect::initialize(QVariantMap param)
{
    if (param.contains("direction"))
        setDirection(param.value("direction").value<HControlType::Direction4>());
}

QString HFlipEffect::typeName()
{
    return "HFlipEffect";
}

void HFlipEffect::draw(QPainter *painter, double factor, const QRect &rect, const QPixmap &pixmap)
{
    Q_D(HFlipEffect);
    QTransform t;
    auto w = rect.width();
    auto h = rect.height();
    auto x = (w - pixmap.width()) / 2;
    auto y = (h - pixmap.height()) / 2;

    if (d->direction == HControlType::Direction4_Left)
    {
        auto r = 90 * (factor - 1);
        t.translate(w * (1 - factor), h / 2.0);
        t.rotate(r, Qt::YAxis);
        t.translate(0, -h / 2.0);
    }
    if (d->direction == HControlType::Direction4_Right)
    {
        auto r = -90 * (factor - 1);
        t.translate(w * factor, h / 2.0);
        t.rotate(r, Qt::YAxis);
        t.translate(-w, -h / 2.0);
    }
    if (d->direction == HControlType::Direction4_Up)
    {
        auto r = 90 * (factor - 1);
        t.translate(w / 2.0, h  * (1 - factor));
        t.rotate(r, Qt::XAxis);
        t.translate(-w / 2.0, 0);
    }
    if (d->direction == HControlType::Direction4_Down)
    {
        auto r = -90 * (factor - 1);
        t.translate(w / 2.0, h  * factor);
        t.rotate(r, Qt::XAxis);
        t.translate(-w/ 2.0, -h);
    }
    painter->save();
    painter->setTransform(t);
    painter->drawPixmap(x, y, pixmap);
    painter->restore();
}

HControlType::Direction4 HFlipEffect::direction() const
{
    Q_D(const HFlipEffect);
    return d->direction;
}

void HFlipEffect::setDirection(HControlType::Direction4 value)
{
    Q_D(HFlipEffect);
    if (value == d->direction)
        return;
    d->direction = value;
}

HE_CONTROL_END_NAMESPACE
