/***************************************************************************************************
**      2018-06-19  IInitializeable 可初始化接口。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QVariant>

HE_BEGIN_NAMESPACE

class IInitializeable
{
public:
    // 初始化
    virtual void initialize(QVariantMap param = QVariantMap()) = 0;
    // 类型名称
    virtual QString typeName() = 0;
};

HE_END_NAMESPACE
