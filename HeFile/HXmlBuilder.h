#ifndef HXMLBUILDER_H
#define HXMLBUILDER_H

#include "HFileGlobal.h"
#include <QVariantMap>

HE_FILE_BEGIN_NAMESPACE

class HXmlElement;

class HE_FILE_EXPORT HXmlBuilder
{
public:
    template<class T>
    static T *createObject(HXmlElement *xe);

    template<class T>
    static T *createObject(HXmlElement *xe, QVariantMap param);
};

HE_FILE_END_NAMESPACE

#endif // HXMLBUILDER_H
