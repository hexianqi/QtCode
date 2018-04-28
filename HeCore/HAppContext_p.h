#ifndef HAPPCONTEXT_P_H
#define HAPPCONTEXT_P_H

#include "HAppContext.h"
#include <QVariant>

HE_CORE_BEGIN_NAMESPACE

class HAppContextPrivate
{
public:
    QHash<QString, QVariant> contextValue;
    QHash<QString, QObject*> contextPointer;
};

HE_CORE_END_NAMESPACE

#endif // HAPPCONTEXT_P_H
