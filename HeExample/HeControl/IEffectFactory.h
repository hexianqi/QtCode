#pragma once

#include "HControlGlobal.h"
#include "HeCore/IInitializeable.h"

class QActionGroup;

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

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

HE_CONTROL_END_NAMESPACE
