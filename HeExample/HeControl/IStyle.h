/***************************************************************************************************
**      2019-07-19  IStyle 样式接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class IStyle : public IInitializeable
{
public:
    // 样式表
    virtual QString toStyleSheet() = 0;
};

HE_END_NAMESPACE
