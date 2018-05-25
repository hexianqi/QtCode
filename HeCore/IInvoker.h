#ifndef IINVOKER_H
#define IINVOKER_H

#include "HeCore/IInitializeable.h"

HE_CORE_BEGIN_NAMESPACE

class IHandler;

// 调用者
class IInvoker : public IInitializeable
{
public:
    // 设置处理者
    virtual void setHandler(IHandler *) = 0;
    // 调用命令类
    virtual void call() = 0;
};

HE_CORE_END_NAMESPACE

#endif // IINVOKER_H
