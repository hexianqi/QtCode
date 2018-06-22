/***************************************************************************************************
**      2018-06-20  HSpecial 特殊函数范例。
***************************************************************************************************/

#ifndef HSPECIAL_H
#define HSPECIAL_H

#include "HExampleGlobal.h"

HE_EXAMPLE_BEGIN_NAMESPACE

class HE_EXAMPLE_EXPORT HSpecial
{
public:
    HSpecial();

public:
    double airyAi(double x);
    double airyBi(double x);
};

HE_EXAMPLE_END_NAMESPACE

#endif // HSPECIAL_H
