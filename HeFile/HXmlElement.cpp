#include "HXmlElement.h"
#include <QDomElement>
#include <QFile>
#include <QTextStream>

HE_FILE_USE_NAMESPACE

HXmlElement *HXmlElement::load(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return nullptr;

    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return nullptr;
    }

    auto root = doc.documentElement();
    auto xe = pares(&root, nullptr, fileName);
    file.close();
    return xe;
}

HXmlElement *HXmlElement::pares(QDomElement *domElement, HXmlElement *parent, QString fileName)
{
    auto xe = new HXmlElement(domElement, parent, fileName);
    auto child = domElement->firstChildElement();
    while (!child.isNull())
    {
        xe->childs().append(pares(&child, xe, fileName));
        child = child.nextSiblingElement();
    }
    return xe;
}

HXmlElement::HXmlElement(QDomElement *domElement, HXmlElement *parent, QString fileName)
{
    _domElement = domElement;
    _parent = parent;
    _fileName = fileName;
}

QString HXmlElement::name()
{
    return _domElement->tagName();
}

HXmlElement *HXmlElement::parent()
{
    return _parent;
}

QList<HXmlElement*> HXmlElement::childs()
{
    return _childs;
}

void HXmlElement::setChild(QList<HXmlElement*> value)
{
    _childs = value;
}

QString HXmlElement::attribute(QString name)
{
    return _domElement->attribute(name);
}

void HXmlElement::setAttribute(QString name, QString value)
{
    _domElement->setAttribute(name, value);
}

bool HXmlElement::save()
{
    return save(_fileName);
}

bool HXmlElement::save(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
        return false;

    QTextStream out(&file);
    _domElement->ownerDocument().save(out, 4);
    return true;
}

HXmlElement *HXmlElement::createChild(QString name)
{
    auto de = _domElement->ownerDocument().createElement(name);
    auto xe = new HXmlElement(&de, this, _fileName);
    _domElement->appendChild(de);
    _childs.append(xe);
    return xe;
}

void HXmlElement::removeChild(HXmlElement *xe)
{
    _childs.removeAll(xe);
    _domElement->removeChild(*xe->_domElement);
    xe->_parent = nullptr;
}

HXmlElement *HXmlElement::findElement(std::function<bool(HXmlElement*)> fun)
{
    if (fun(this))
        return this;

    HXmlElement* xe = nullptr;
    for (auto item : _childs)
    {
        xe = item->findElement(fun);
        if (xe != nullptr)
            return xe;
    }
    return xe;
}

QList<HXmlElement*> HXmlElement::findElementAll(std::function<bool(HXmlElement*)> fun)
{
    QList<HXmlElement*> list;
    if (fun(this))
        list << this;
    for (auto item : _childs)
        list << item->findElementAll(fun);
    return list;
}

void HXmlElement::forEach(std::function<void(HXmlElement*)> fun)
{
    fun(this);
    for (auto item : _childs)
        item->forEach(fun);
}

