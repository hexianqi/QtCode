#ifndef IINITIALIZEABLE_H
#define IINITIALIZEABLE_H

#include "HCoreGlobal.h"
#include <QVariant>

HE_CORE_BEGIN_NAMESPACE

// 可初始化接口
class HE_CORE_EXPORT IInitializeable
{
public:
    virtual void initialize(QVariantMap param) = 0;
};

HE_CORE_END_NAMESPACE

#endif // IINITIALIZEABLE_H
