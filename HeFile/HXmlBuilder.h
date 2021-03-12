/***************************************************************************************************
**      2018-06-19  HXmlBuilder XML构建器。
***************************************************************************************************/

#pragma once

#include "HFileGlobal.h"
#include <QtCore/QVariant>

HE_FILE_BEGIN_NAMESPACE

class HXmlElement;

class HE_FILE_EXPORT HXmlBuilder
{
public:
    // 创建对象
    template <typename T>
    static T *createObject(HXmlElement *xe);
    // 创建对象
    template <typename T>
    static T *createObject(HXmlElement *xe, QVariantMap param);
};

HE_FILE_END_NAMESPACE
