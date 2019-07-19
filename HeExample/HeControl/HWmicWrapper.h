/***************************************************************************************************
**      2019-07-16  HWmicWrapper WMIC包装
***************************************************************************************************/

#ifndef HWMICWRAPPER_H
#define HWMICWRAPPER_H

#include "HControlGlobal.h"

HE_CONTROL_BEGIN_NAMESPACE

class HWmicWrapper
{
public:
    static QString getCpuName();
    static QString getCpuId();
    static QString getDiskNum();
};

HE_CONTROL_END_NAMESPACE

#endif // HWMICWRAPPER_H
