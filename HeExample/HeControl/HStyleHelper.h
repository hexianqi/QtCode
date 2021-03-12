/***************************************************************************************************
**      2020-04-01  HStyleHelper 样式帮助类。
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"

HE_CONTROL_BEGIN_NAMESPACE

class HStyleHelper
{
public:
    // 从文件中加载样式
    static QString loadStyle(const QString &fileName);
};

HE_CONTROL_END_NAMESPACE
