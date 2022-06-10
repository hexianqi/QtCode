/***************************************************************************************************
**      2019-05-23  一些模板函数。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QMetaEnum>
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

// 枚举转字符串
template <typename EnumType>
const char* enumToString(EnumType value)
{
    static_assert(std::is_enum<EnumType>::value, "EnumType must be enum");
    return QMetaEnum::fromType<EnumType>().valueToKey(value);
}

// 字符串转枚举
template <typename EnumType>
EnumType stringToEnum(const char *value, bool *ok = nullptr)
{
    static_assert(std::is_enum<EnumType>::value, "EnumType must be enum");
    return EnumType(QMetaEnum::fromType<EnumType>().keyToValue(value, ok));
}

HE_END_NAMESPACE
