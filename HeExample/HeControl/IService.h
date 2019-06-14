/***************************************************************************************************
**      2019-06-10  IService 服务接口。
***************************************************************************************************/

#ifndef ISERVICE_H
#define ISERVICE_H

#include "HControlGlobal.h"

HE_CONTROL_BEGIN_NAMESPACE

class IService
{
public:
    // 启动服务
    virtual void start() = 0;
    // 停止服务
    virtual void stop() = 0;
};

HE_CONTROL_END_NAMESPACE

#endif // ISERVICE_H
