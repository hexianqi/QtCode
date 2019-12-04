/***************************************************************************************************
**      2019-06-06  IEventFilter 事件过滤器。
***************************************************************************************************/

#ifndef IEVENTFILTER_H
#define IEVENTFILTER_H

#include "HControlGlobal.h"
#include <QtCore/QEvent>
#include <functional>

class QObject;
class QRectF;

HE_CONTROL_BEGIN_NAMESPACE

class IEventFilter
{
public:
    // 设置有效范围
    virtual bool setValidRegion(QRectF value) = 0;
    // 设置是否启用
    virtual bool setEnable(bool b) = 0;
    // 是否启用
    virtual bool isEnable() = 0;
    // 添加处理函数
    virtual void addHandle(QEvent::Type type, std::function<bool(QEvent *)> func) = 0;

public:
    // 事件过滤器
    virtual bool eventFilter(QObject *, QEvent *) = 0;
};

HE_CONTROL_END_NAMESPACE

#endif // IEVENTFILTER_H
