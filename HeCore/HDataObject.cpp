#include "HDataObject.h"
#include "HDataObject_p.h"
#include <QString>
#include "IInitializeable.h"

HE_CORE_BEGIN_NAMESPACE

QString removeBracket(QString text)
{
    text.remove(QChar('['));
    text.remove(QChar(']'));
    return text;
}

HDataObject::HDataObject(QString type)
    : d_ptr(new HDataObjectPrivate)
{
    d_ptr->type = type;
}

HDataObject::HDataObject(const HDataObject &rhs)
    : d_ptr(rhs.d_ptr)
{
}

HDataObject::HDataObject(HDataObjectPrivate &p)
    : d_ptr(&p)
{
}

HDataObject &HDataObject::operator=(const HDataObject &rhs)
{
    if (this != &rhs)
        d_ptr.operator=(rhs.d_ptr);
    return *this;
}

HDataObject::~HDataObject()
{
}

QString HDataObject::tr(const char *sourceText, const char *comment, int n)
{
    return QObject::tr(sourceText, comment, n);
}

void HDataObject::initialize(QVariantMap param)
{
    if (param.contains("type"))
        setType(param["type"].toString());
}

void HDataObject::setType(QString value)
{
    Q_D(HDataObject);
    d->type = QChar('[') + removeBracket(value) + QChar(']');;
}

QString HDataObject::type(bool bracket) const
{
    Q_D(const HDataObject);
    return bracket ? d->type : removeBracket(d->type);
}

HE_CORE_END_NAMESPACE
