/***************************************************************************************************
**      2020-04-01  HStyleHelper 样式帮助类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"

class QString;

HE_BEGIN_NAMESPACE

class HStyleHelper
{
public:
    // 从文件中加载样式
    static QString loadStyle(const QString &fileName);
};

HE_END_NAMESPACE
