/***************************************************************************************************
**      2019-06-12  IStyleFactory 样式工厂接口。
***************************************************************************************************/

#ifndef ISTYLEFACTORY_H
#define ISTYLEFACTORY_H

#include "HControlGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

class IStyle;

class IStyleFactory : public IInitializeable
{
public:
    // 所有样式
    virtual QStringList keys() = 0;
    // 创建样式
    virtual IStyle *create(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_CONTROL_END_NAMESPACE

#endif // ISTYLEFACTORY_H
