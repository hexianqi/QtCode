/***************************************************************************************************
**      2019-08-20  HXmlHelper Xml帮助类。
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"

class QDomElement;

HE_CONTROL_BEGIN_NAMESPACE

class HXmlHelper
{
public:
    // 修改属性
    static void setAttribute(QDomElement elem, const QString &tagName, const QString &attributeName, const QString &attributeValue);
};

HE_CONTROL_END_NAMESPACE
