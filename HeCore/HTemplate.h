/***************************************************************************************************
**      2019-05-23  一些模板函数。
***************************************************************************************************/

#ifndef HTEMPLATE_H
#define HTEMPLATE_H

#include "HCoreGlobal.h"
#include <cxxabi.h>

HE_CORE_BEGIN_NAMESPACE

// 获取类名称
template <typename T>
char *className()
{
    return abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
}

HE_CORE_END_NAMESPACE

#endif // HTEMPLATE_H
