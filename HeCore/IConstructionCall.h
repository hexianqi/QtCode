/***************************************************************************************************
**      2019-03-04  IConstructionCall 构造函数中调用虚函数接口。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"

HE_BEGIN_NAMESPACE

class IConstructionCall
{
public:
    // 初始化
    virtual void initialize() = 0;
};

class HConstructionCallHelper
{
public:
    HConstructionCallHelper();
    ~HConstructionCallHelper();

public:
    void initialize(IConstructionCall *) const;

private:
    mutable IConstructionCall *_p;
};

HE_END_NAMESPACE
