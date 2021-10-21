/***************************************************************************************************
**      2019-07-19  IStyle 样式接口。
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

class IStyle : public IInitializeable
{
public:
    // 样式表
    virtual QString toStyleSheet() = 0;
};

HE_CONTROL_END_NAMESPACE
