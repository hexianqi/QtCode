/***************************************************************************************************
**      2019-07-16  HWmicHelper WMIC帮助类。
***************************************************************************************************/

#ifndef HWMICWRAPPER_H
#define HWMICWRAPPER_H

#include "HControlGlobal.h"

HE_CONTROL_BEGIN_NAMESPACE

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

HE_CONTROL_END_NAMESPACE

#endif // HWMICWRAPPER_H
