/***************************************************************************************************
**      2018-06-19  IInvoker 调用者接口。
***************************************************************************************************/

#pragma once

#include "IInitializeable.h"

HE_CORE_BEGIN_NAMESPACE

class IHandler;

class IInvoker : public IInitializeable
{
public:
    // 设置处理者
    virtual void setHandler(IHandler *) = 0;
    // 调用命令类
    virtual void call() = 0;
};

HE_CORE_END_NAMESPACE
