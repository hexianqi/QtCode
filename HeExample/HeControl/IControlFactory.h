/***************************************************************************************************
**      2019-06-13  IControlFactory 控件工厂接口。
***************************************************************************************************/

#ifndef ICONTROLFACTORY_H
#define ICONTROLFACTORY_H

#include "HControlGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

class IEventFilter;

class IControlFactory : public IInitializeable
{
public:
    // 支持的窗体
    virtual QStringList supportedWidgets() = 0;
    // 支持的事件过滤器
    virtual QStringList supportedEventFilters() = 0;
    // 创建窗体
    virtual QWidget *createWidget(const QString &type, QWidget *parent = nullptr) = 0;
    // 创建事件过滤器
    virtual IEventFilter *createEventFilter(const QString &type, QVariantMap param = QVariantMap()) = 0;
};

HE_CONTROL_END_NAMESPACE

#endif // ICONTROLFACTORY_H
