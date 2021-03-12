/***************************************************************************************************
**      2019-03-21  IBuilder 创建者接口。
***************************************************************************************************/

#pragma once

#include "HGuiGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class IBuilder : public IInitializeable
{
public:
    // 创建所有
    virtual void buildAll() = 0;
};

HE_GUI_END_NAMESPACE
