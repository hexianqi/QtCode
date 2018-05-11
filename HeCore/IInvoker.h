#ifndef IINVOKER_H
#define IINVOKER_H

#include "HeCore/IInitializeable.h"

HE_CORE_BEGIN_NAMESPACE

class IHandler;

class HE_CORE_EXPORT IInvoker : public IInitializeable
{
//public:
//    virtual ~IInvoker() = default;

public:
    virtual void setHandler(IHandler *handler) = 0;
    virtual void call() = 0;
};

HE_CORE_END_NAMESPACE

#endif // IINVOKER_H
