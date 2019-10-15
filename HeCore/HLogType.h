/***************************************************************************************************
**      2019-10-09  HLogType 日志类型。
***************************************************************************************************/

#ifndef HLOGTYPE_H
#define HLOGTYPE_H

#include "HCoreGlobal.h"

HE_CORE_BEGIN_NAMESPACE

enum HLogType
{
    Reset = 0,
    Bold,
    Unbold,
    ForeBlack,
    ForeRed,
    ForeGreen,
    ForeYellow,
    ForeBlue,
    ForePurple,
    ForeCyan,
    ForeWhite,
    BackBlack,
    BackRed,
    BackGreen,
    BackYellow,
    BackBlue,
    BackPurple,
    BackCyan,
    BackWhite,
    TypeCount
};

HE_CORE_END_NAMESPACE

#endif // HLOGTYPE_H
