/***************************************************************************************************
**      2019-05-23  一些模板函数。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <cxxabi.h>

HE_BEGIN_NAMESPACE

// 获取类名称
template <typename T>
char *className()
{
    return abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
}

HE_END_NAMESPACE
