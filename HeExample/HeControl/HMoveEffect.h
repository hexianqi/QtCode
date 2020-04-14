/***************************************************************************************************
**      2019-07-25  HMoveEffect 移动特效
***************************************************************************************************/

#ifndef HMOVEEFFECT_H
#define HMOVEEFFECT_H

#include "HAbstractShaderEffect.h"
#include "HControlType.h"

HE_CONTROL_BEGIN_NAMESPACE

class HMoveEffectPrivate;

class HMoveEffect : public HAbstractShaderEffect
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMoveEffect)
    Q_PROPERTY(HControlType::Direction4 direction READ direction WRITE setDirection)


public:
    explicit HMoveEffect(QObject *parent = nullptr);

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
    HMoveEffect(HMoveEffectPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HMOVEEFFECT_H
