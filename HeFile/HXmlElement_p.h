#pragma once

#include "HXmlElement.h"
#include <QtCore/QStringList>

HE_FILE_BEGIN_NAMESPACE

class HXmlElementPrivate
{
public:
    HXmlElementPrivate(const QString &fileName, QDomElement *domElement, HXmlElement *parent);

public:
    QString fileName;
    QDomElement *domElement;
    HXmlElement *parent;
    QList<HXmlElement*> childs;
};

HE_FILE_END_NAMESPACE
