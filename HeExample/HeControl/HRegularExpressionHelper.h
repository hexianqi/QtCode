/***************************************************************************************************
**      2019-12-17  HRegularExpressionHelper 正则表达式帮助类。
***************************************************************************************************/

#ifndef HREGULAREXPRESSIONHELPER_H
#define HREGULAREXPRESSIONHELPER_H

#include "HControlGlobal.h"

HE_CONTROL_BEGIN_NAMESPACE

class HRegularExpressionHelper
{
public:
    // 是否匹配
    static bool isMatch(const QString &text, const QString &pattern);
    // 是否IP
    static bool isIP(const QString &text);
};

HE_CONTROL_END_NAMESPACE

#endif // HREGULAREXPRESSIONHELPER_H
