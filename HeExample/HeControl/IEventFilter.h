/***************************************************************************************************
**      2019-06-06  IEventFilter 事件过滤器。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"
#include <QtCore/QEvent>

HE_BEGIN_NAMESPACE

class IEventFilter: public IInitializeable
{
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

HE_END_NAMESPACE
