#include "HXmlHelper.h"
#include <QtXml/QDomElement>

HE_CONTROL_BEGIN_NAMESPACE

void HXmlHelper::setAttribute(QDomElement elem, const QString &tagName, const QString &attributeName, const QString &attributeValue)
{
    if (elem.tagName().compare(tagName) == 0)
        elem.setAttribute(attributeName, attributeValue);

    for (int i = 0; i < elem.childNodes().count(); i++)
    {
        if (!elem.childNodes().at(i).isElement())
            continue;
        setAttribute(elem.childNodes().at(i).toElement(), tagName, attributeName, attributeValue);
    }
}

HE_CONTROL_END_NAMESPACE
