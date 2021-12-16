/***************************************************************************************************
**      2019-07-24  HBlindsEffect 百叶窗
***************************************************************************************************/

#pragma once

#include "HAbstractShaderEffect.h"
#include "HControlType.h"

HE_BEGIN_NAMESPACE

class HBlindsEffectPrivate;

class HBlindsEffect : public HAbstractShaderEffect
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBlindsEffect)
    Q_PROPERTY(int page READ page WRITE setPage)
    Q_PROPERTY(HControlType::Direction4 direction READ direction WRITE setDirection)

public:
    explicit HBlindsEffect(QObject *parent = nullptr);

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    void draw(QPainter *, double factor, const QRect &rect, const QPixmap &pixmap) override;

public:
    int page() const;
    HControlType::Direction4 direction() const;

public slots:
    void setPage(int value);
    void setDirection(HControlType::Direction4 value);

protected:
    HBlindsEffect(HBlindsEffectPrivate &p, QObject *parent = nullptr);
};

HE_END_NAMESPACE
