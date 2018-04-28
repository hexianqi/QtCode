#ifndef HTYPEHELPER_H
#define HTYPEHELPER_H

#include "HCoreGlobal.h"
#include "HeFile/HFileGlobal.h"
#include <QVariant>

HE_CORE_BEGIN_NAMESPACE

class HE_CORE_EXPORT HTypeHelper
{
public:
    template<class T>
    static T *createObject(QString className);

    template<class T>
    static T *createObject(QString className, QVariantMap param);
};

HE_CORE_END_NAMESPACE

#endif // HTYPEHELPER_H
