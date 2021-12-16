/***************************************************************************************************
**      2018-06-19  HXmlBuilder XML构建器。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QVariant>

HE_BEGIN_NAMESPACE

class HXmlElement;

class HXmlBuilder
{
public:
    // 创建对象
    template <typename T>
    static T *createObject(HXmlElement *xe);
    // 创建对象
    template <typename T>
    static T *createObject(HXmlElement *xe, QVariantMap param);
};

HE_END_NAMESPACE
