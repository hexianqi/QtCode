#ifndef HXMLELEMENT_P_H
#define HXMLELEMENT_P_H

#include "HXmlElement.h"
#include <QtCore/QStringList>

HE_FILE_BEGIN_NAMESPACE

class HXmlElementPrivate
{
public:
    HXmlElementPrivate(QString fileName, QDomElement *domElement, HXmlElement *parent);

public:
    QString fileName;
    QDomElement *domElement;
    HXmlElement *parent;
    QList<HXmlElement*> childs;
};

HE_FILE_END_NAMESPACE

#endif // HXMLELEMENT_P_H
