/***************************************************************************************************
**      2019-08-20  HXmlHelper Xml帮助类。
***************************************************************************************************/

#ifndef HXMLHELPER_H
#define HXMLHELPER_H

#include "HControlGlobal.h"

class QDomElement;
class QColor;

HE_CONTROL_BEGIN_NAMESPACE

class HXmlHelper
{
public:
    // 修改属性
    static void setAttribute(QDomElement elem, const QString &tagName, const QString &attributeName, const QString &attributeValue);
};

HE_CONTROL_END_NAMESPACE

#endif // HXMLHELPER_H
