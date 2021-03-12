/***************************************************************************************************
**      2019-05-17  ICloneable 支持克隆，即用与现有实例相同的值创建类的新实例。
***************************************************************************************************/

#pragma once

#include "HCoreGlobal.h"

HE_CORE_BEGIN_NAMESPACE

template <typename T>
class ICloneable
{
public:
    // 创建当前实例副本的新对象。
    virtual T *clone() = 0;
};

HE_CORE_END_NAMESPACE

