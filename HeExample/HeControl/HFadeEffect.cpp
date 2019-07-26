#include "HFadeEffect_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HFadeEffect::HFadeEffect(QObject *parent) :
    HAbstractShaderEffect(*new HFadeEffectPrivate, parent)
{
}

HFadeEffect::HFadeEffect(HFadeEffectPrivate &p, QObject *parent) :
    HAbstractShaderEffect(p, parent)
{
}

HFadeEffect::~HFadeEffect()
{
}

void HFadeEffect::initialize(QVariantMap /*param*/)
{

}

QString HFadeEffect::typeName()
{
    return "HFadeEffect";
}

void HFadeEffect::draw(QPainter *painter, double factor, const QRect &rect, const QPixmap &pixmap)
{
    auto x = (rect.width() - pixmap.width()) / 2;
    auto y = (rect.height() - pixmap.height()) / 2;
    auto a = static_cast<int>(255 * factor);

    QPixmap pm(pixmap.size());
    pm.fill(Qt::transparent);
    QPainter p(&pm);
    p.setCompositionMode(QPainter::CompositionMode_Source);
    p.drawPixmap(0, 0, pixmap);
    p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p.fillRect(pm.rect(), QColor(0, 0, 0, a));
    p.end();

    painter->save();
    painter->drawPixmap(x, y, pm);
    painter->restore();
}

HE_CONTROL_END_NAMESPACE
