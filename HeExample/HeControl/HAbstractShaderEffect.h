/***************************************************************************************************
**      2019-07-24  HAbstractShaderEffect 抽象特效。
***************************************************************************************************/

#pragma once

#include "IShaderEffect.h"

HE_BEGIN_NAMESPACE

class HAbstractShaderEffectPrivate;

class HAbstractShaderEffect : public QObject, public IShaderEffect
{
    Q_OBJECT

public:
    explicit HAbstractShaderEffect(QObject *parent = nullptr);
    ~HAbstractShaderEffect() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;

protected:
    HAbstractShaderEffect(HAbstractShaderEffectPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractShaderEffectPrivate> d_ptr;
};

HE_END_NAMESPACE
