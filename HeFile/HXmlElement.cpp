#include "HXmlElement_p.h"
#include <QDomElement>
#include <QFile>
#include <QTextStream>

HE_FILE_BEGIN_NAMESPACE

HXmlElementPrivate::HXmlElementPrivate(QString fileName, QDomElement *domElement, HXmlElement *parent)
{
    this->fileName = fileName;
    this->domElement = domElement;
    this->parent = parent;
}

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
    auto xe = parse(fileName, &root, nullptr);
    file.close();
    return xe;
}

HXmlElement *HXmlElement::parse(QString fileName, QDomElement *domElement, HXmlElement *parent)
{
    auto xe = new HXmlElement(fileName, domElement, parent);
    auto child = domElement->firstChildElement();
    while (!child.isNull())
    {
        xe->childs().append(parse(fileName, &child, xe));
        child = child.nextSiblingElement();
    }
    return xe;
}

HXmlElement::HXmlElement(QString fileName, QDomElement *domElement, HXmlElement *parent)
    : d_ptr(new HXmlElementPrivate(fileName, domElement, parent))
{
}

HXmlElement::HXmlElement(HXmlElementPrivate &p)
    : d_ptr(&p)
{
}

QString HXmlElement::name()
{
    return d_ptr->domElement->tagName();
}

HXmlElement *HXmlElement::parent()
{
    return d_ptr->parent;
}

QList<HXmlElement*> HXmlElement::childs()
{
    return d_ptr->childs;
}

void HXmlElement::setChild(QList<HXmlElement*> value)
{
    d_ptr->childs = value;
}

QString HXmlElement::attribute(QString name)
{
    return d_ptr->domElement->attribute(name);
}

void HXmlElement::setAttribute(QString name, QString value)
{
    d_ptr->domElement->setAttribute(name, value);
}

bool HXmlElement::save()
{
    return save(d_ptr->fileName);
}

bool HXmlElement::save(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
        return false;

    QTextStream out(&file);
    d_ptr->domElement->ownerDocument().save(out, QDomNode::EncodingFromDocument);
    file.close();
    return true;
}

HXmlElement *HXmlElement::createChild(QString name)
{
    auto de = d_ptr->domElement->ownerDocument().createElement(name);
    auto xe = new HXmlElement(d_ptr->fileName, &de, this);
    d_ptr->domElement->appendChild(de);
    d_ptr->childs.append(xe);
    return xe;
}

void HXmlElement::removeChild(HXmlElement *xe)
{
    d_ptr->childs.removeAll(xe);
    d_ptr->domElement->removeChild(*xe->d_ptr->domElement);
    xe->d_ptr->parent = nullptr;
}

HXmlElement *HXmlElement::findElement(std::function<bool(HXmlElement*)> func)
{
    if (func(this))
        return this;

    HXmlElement* xe = nullptr;
    for (auto item : childs())
    {
        xe = item->findElement(func);
        if (xe != nullptr)
            return xe;
    }
    return xe;
}

QList<HXmlElement*> HXmlElement::findElementAll(std::function<bool(HXmlElement*)> func)
{
    QList<HXmlElement*> list;
    if (func(this))
        list << this;
    for (auto item : childs())
        list << item->findElementAll(func);
    return list;
}

void HXmlElement::forEach(std::function<void(HXmlElement*)> func)
{
    func(this);
    for (auto item : childs())
        item->forEach(func);
}

HE_FILE_END_NAMESPACE
