/***************************************************************************************************
**      2019-06-06  IEventFilter 事件过滤器。
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include "HeCore/IInitializeable.h"
#include <QtCore/QEvent>

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

class IEventFilter: public QObject, public IInitializeable
{
    Q_OBJECT

public:
    using QObject::QObject;

public:
    // 设置是否启用
    virtual bool setEnable(bool b) = 0;
    // 是否启用
    virtual bool isEnable() = 0;
    // 添加观测对象
    virtual bool addWatched(QObject *) = 0;
    // 添加处理函数
    virtual void addHandler(QEvent::Type type, std::function<bool(QEvent *)> func) = 0;

public:
    // 事件过滤器
    virtual bool eventFilter(QObject *, QEvent *) = 0;
};

HE_CONTROL_END_NAMESPACE
