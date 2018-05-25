#ifndef IINITIALIZEABLE_H
#define IINITIALIZEABLE_H

#include "HCoreGlobal.h"
#include <QVariant>

HE_CORE_BEGIN_NAMESPACE

// 可初始化接口
class IInitializeable
{
public:
    // 类型名称
    virtual QString typeName() = 0;
    // 初始化
    virtual void initialize(QVariantMap param) = 0;
};

HE_CORE_END_NAMESPACE

#endif // IINITIALIZEABLE_H
