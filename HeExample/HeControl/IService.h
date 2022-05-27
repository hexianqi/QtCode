/***************************************************************************************************
**      2019-06-10  IService 服务接口。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"

HE_BEGIN_NAMESPACE

class IService
{
public:
    // 启动服务
    virtual bool start() = 0;
    // 停止服务
    virtual bool stop() = 0;
};

HE_END_NAMESPACE
