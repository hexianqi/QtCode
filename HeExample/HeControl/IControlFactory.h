/***************************************************************************************************
**      2019-06-13  IControlFactory 控件工厂接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class IEventFilter;

class IControlFactory : public IInitializeable
{
public:
    // 支持的窗体
    virtual QStringList supportedWidget() = 0;
    // 创建窗体
    virtual QWidget *createWidget(const QString &type, QWidget *parent = nullptr) = 0;
    // 支持的事件过滤器
    virtual QStringList supportedEventFilter() = 0;
    // 创建事件过滤器
    virtual IEventFilter *createEventFilter(const QString &type, QVariantMap param = QVariantMap()) = 0;
};

HE_END_NAMESPACE
