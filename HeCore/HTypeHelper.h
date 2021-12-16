/***************************************************************************************************
**      2018-06-19  HTypeHelper 元类型帮助类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QVariant>

HE_BEGIN_NAMESPACE

class HTypeHelper
{
public:
    // 创建对象
    template <typename T>
    static T *createObject(const QString &className);
    // 创建对象
    template <typename T>
    static T *createObject(const QString &className, QVariantMap param);
};

HE_END_NAMESPACE
