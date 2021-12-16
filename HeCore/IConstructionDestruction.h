/***************************************************************************************************
**      2021-12-17  IConstructionDestruction 构造函数后调用函数，析构函数前调用函数接口。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <type_traits>

HE_BEGIN_NAMESPACE

class IConstructionDestruction
{
public:
    // 构造后调用函数
    virtual void afterConstruction() = 0;
    // 析构前调用函数
    virtual void beforeDestruction() = 0;
};

template <class T>
class TConstructionDestruction : public T
{
public:
    TConstructionDestruction()
    {
        static_assert(std::is_base_of<IConstructionDestruction, T>::value, "T needs to be IConstructionDestruction based.");
        this->afterConstruction();
    }
    ~TConstructionDestruction()
    {
        static_assert(std::is_base_of<IConstructionDestruction, T>::value, "T needs to be IConstructionDestruction based.");
        this->beforeDestruction();
    }
};

HE_END_NAMESPACE
