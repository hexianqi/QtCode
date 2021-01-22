/***************************************************************************************************
**      2019-10-24  IActionStrategy 动作处理接口。
***************************************************************************************************/

#ifndef IACTIONSTRATEGY_H
#define IACTIONSTRATEGY_H

#include "HControllerGlobal.h"
#include "HeCore/IInitializeable.h"
#include "HeCore/HActionType.h"
#include "HeCommunicate/HCommunicateGlobal.h"

HE_CORE_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE
class IProtocol;
HE_COMMUNICATE_END_NAMESPACE
HE_COMMUNICATE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HE_CONTROLLER_EXPORT IActionStrategy : public QObject, public IInitializeable
{
    Q_OBJECT

public:
    using QObject::QObject;

public:
    // 设置协议
    virtual void setProtocol(IProtocol *) = 0;
    // 是否支持动作
    virtual bool isSupport(HActionType action) = 0;
    // 处理动作
    virtual bool handle(HActionType action) = 0;
};

HE_CONTROLLER_END_NAMESPACE

#endif // IACTIONSTRATEGY_H
