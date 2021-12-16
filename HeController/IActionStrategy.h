/***************************************************************************************************
**      2019-10-24  IActionStrategy 动作处理接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"
#include "HeCore/HActionType.h"

HE_BEGIN_NAMESPACE

class IProtocol;

class IActionStrategy : public IInitializeable
{
public:
    // 设置协议
    virtual void setProtocol(IProtocol *) = 0;
    // 是否支持动作
    virtual bool isSupport(HActionType action) = 0;
    // 处理动作
    virtual bool handle(HActionType action) = 0;
};

HE_END_NAMESPACE
