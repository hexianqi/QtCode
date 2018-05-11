#ifndef IHANDLER_H
#define IHANDLER_H

#include "HeCore/IInitializeable.h"

HE_CORE_BEGIN_NAMESPACE

class HE_CORE_EXPORT IHandler : public IInitializeable
{
public:
    virtual void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) = 0;
};

HE_CORE_END_NAMESPACE

#endif // IHANDLER_H
