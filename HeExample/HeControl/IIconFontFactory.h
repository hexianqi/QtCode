/***************************************************************************************************
**      2019-12-12  IIconFontFactory 图标字体接口。
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE
HE_CONTROL_BEGIN_NAMESPACE

class IIconFontFactory : public IInitializeable
{
public:
    // 所有字体
    virtual QStringList families() = 0;
    // 创建字体
    virtual QFont createFont(const QString &family) = 0;
};

HE_CONTROL_END_NAMESPACE
