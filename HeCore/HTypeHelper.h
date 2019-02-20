/***************************************************************************************************
**      2018-06-19  HTypeHelper 元类型帮助类。
***************************************************************************************************/

#ifndef HTYPEHELPER_H
#define HTYPEHELPER_H

#include "HCoreGlobal.h"
#include <QVariant>

HE_CORE_BEGIN_NAMESPACE

class HTypeHelper
{
public:
    // 创建对象
    template<class T>
    static T *createObject(QString className);
    // 创建对象
    template<class T>
    static T *createObject(QString className, QVariantMap param);
};

HE_CORE_END_NAMESPACE

#endif // HTYPEHELPER_H
