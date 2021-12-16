/***************************************************************************************************
**      2019-12-17  HRegularExpressionHelper 正则表达式帮助类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"

class QObject;
class QString;
class QRegularExpressionValidator;

HE_BEGIN_NAMESPACE

class HRegularExpressionHelper
{
public:
    // 是否匹配
    static bool isMatch(const QString &text, const QString &pattern);
    // 是否IP
    static bool isIP(const QString &text);
    // 邮箱
    static QRegularExpressionValidator *email(QObject *parent = nullptr);
};

HE_END_NAMESPACE
