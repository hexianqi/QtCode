/***************************************************************************************************
**      2019-05-23  一些模板函数。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <cxxabi.h>
#include <type_traits>

HE_BEGIN_NAMESPACE

// 获取类名称
template <typename T>
char *className()
{
    return abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
}

// 枚举转整形
template <typename EnumType, typename IntType = int>
int enumToInt(EnumType value)
{
    static_assert(std::is_enum<EnumType>::value, "EnumType must be enum");
    return static_cast<IntType>(value);
}

HE_END_NAMESPACE
