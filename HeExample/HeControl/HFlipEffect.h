/***************************************************************************************************
**      2019-07-24  HFlipEffect 翻滚特效
***************************************************************************************************/

#ifndef HFLIPEFFECT_H
#define HFLIPEFFECT_H

#include "HAbstractShaderEffect.h"
#include "HControlType.h"

HE_CONTROL_BEGIN_NAMESPACE

class HFlipEffectPrivate;

class HFlipEffect : public HAbstractShaderEffect
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HFlipEffect)
    Q_PROPERTY(HControlType::Direction4 direction READ direction WRITE setDirection)

public:
    explicit HFlipEffect(QObject *parent = nullptr);

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(QPainter *, double factor, const QRect &rect, const QPixmap &pixmap) override;

public:
    HControlType::Direction4 direction() const;

public slots:
    void setDirection(HControlType::Direction4 value);

protected:
    HFlipEffect(HFlipEffectPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HFLIPEFFECT_H
