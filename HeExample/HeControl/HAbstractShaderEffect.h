/***************************************************************************************************
**      2019-07-24  HAbstractShaderEffect 抽象特效。
***************************************************************************************************/

#pragma once

#include "IShaderEffect.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractShaderEffectPrivate;

class HAbstractShaderEffect : public QObject, public IShaderEffect
{
    Q_OBJECT

public:
    explicit HAbstractShaderEffect(QObject *parent = nullptr);
    ~HAbstractShaderEffect() override;

public:
    void initialize(QVariantMap param) override;

protected:
    HAbstractShaderEffect(HAbstractShaderEffectPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractShaderEffectPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE
