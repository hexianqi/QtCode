/***************************************************************************************************
**      2018-06-19  HXmlBuilder XML构建器。
***************************************************************************************************/

#ifndef HXMLBUILDER_H
#define HXMLBUILDER_H

#include "HFileGlobal.h"
#include <QVariantMap>

HE_FILE_BEGIN_NAMESPACE

class HXmlElement;

class HE_FILE_EXPORT HXmlBuilder
{
public:
    template <typename T>
    static T *createObject(HXmlElement *xe);

    template <typename T>
    static T *createObject(HXmlElement *xe, QVariantMap param);
};

HE_FILE_END_NAMESPACE

#endif // HXMLBUILDER_H
