/***************************************************************************************************
**      2019-07-11
***************************************************************************************************/

#ifndef HCONTROLTYPE_H
#define HCONTROLTYPE_H

#include "HControlGlobal.h"

HE_CONTROL_BEGIN_NAMESPACE

enum PointerStyle
{
    PointerStyle_Circle = 0,        // 圆形指示器
    PointerStyle_Indicator = 1,     // 指针指示器
    PointerStyle_IndicatorR = 2,    // 圆角指针指示器
    PointerStyle_Triangle = 3       // 三角形指示器
};

HE_CONTROL_END_NAMESPACE

#endif // HCONTROLTYPE_H
