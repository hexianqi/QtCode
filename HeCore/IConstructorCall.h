/***************************************************************************************************
**      2019-03-04  IConstructorCall 构造函数中调用虚函数接口。
***************************************************************************************************/

#ifndef ICONSTRUCTORCALL_H
#define ICONSTRUCTORCALL_H

#include "HCoreGlobal.h"

HE_CORE_BEGIN_NAMESPACE

class IConstructorCall
{
public:
    // 初始化
    virtual void initialize() = 0;
};

HE_CORE_END_NAMESPACE


#endif // ICONSTRUCTORCALL_H
