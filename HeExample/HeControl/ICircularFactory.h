/***************************************************************************************************
**      2019-06-19  ICircularFactory 工厂接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

class QActionGroup;

HE_BEGIN_NAMESPACE

class ICircular;

class ICircularFactory : public IInitializeable
{
public:
    // 所有样式
    virtual QStringList keys() = 0;
    // 创建样式
    virtual ICircular *create(QString type, QVariantMap param = QVariantMap()) = 0;
    // 转换成动作组
    virtual QActionGroup *toActionGroup() = 0;
};

HE_END_NAMESPACE
