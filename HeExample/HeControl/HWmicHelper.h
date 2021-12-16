/***************************************************************************************************
**      2019-07-16  HWmicHelper WMIC帮助类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"

class QString;

HE_BEGIN_NAMESPACE

class HWmicHelper
{
public:
    // 获取CPU名称
    static QString cpuName();
    // 查询CPU序列号
    static QString cpuId();
    // 查看硬盘
    static QString diskNum();
};

HE_END_NAMESPACE
