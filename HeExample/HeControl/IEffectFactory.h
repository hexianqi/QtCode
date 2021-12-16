#pragma once

#include "HeCore/IInitializeable.h"

class QActionGroup;

HE_BEGIN_NAMESPACE

class IShaderEffect;

class IEffectFactory : public IInitializeable
{
public:
    // 所有特效
    virtual QStringList keys() = 0;
    // 创建特效
    virtual IShaderEffect *create(QString type, QVariantMap param = QVariantMap()) = 0;
    // 转换成动作组
    virtual QActionGroup *toActionGroup() = 0;
};

HE_END_NAMESPACE
