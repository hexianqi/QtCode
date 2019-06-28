/***************************************************************************************************
**      2019-06-19  ICircularFactory 工厂接口。
***************************************************************************************************/

#ifndef ICIRCULARFACTORY_H
#define ICIRCULARFACTORY_H

#include "HControlGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

class ICircular;

class ICircularFactory : public IInitializeable
{
public:
    // 所有样式
    virtual QStringList keys() = 0;
    // 名称
    virtual QString alias(QString type) = 0;
    // 创建样式
    virtual ICircular *create(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_CONTROL_END_NAMESPACE

#endif // ICIRCULARFACTORY_H
