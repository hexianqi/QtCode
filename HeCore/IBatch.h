/***************************************************************************************************
**      2019-05-24  IBatch 批处理接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_CORE_BEGIN_NAMESPACE

class IHandler;

class IBatch : public IInitializeable
{
public:
    // 添加处理者
    virtual void addHandler(IHandler *) = 0;
    // 删除处理者
    virtual void removeHandler(IHandler *) = 0;
    // 调用命令类
    virtual void call() = 0;
};

HE_CORE_END_NAMESPACE
