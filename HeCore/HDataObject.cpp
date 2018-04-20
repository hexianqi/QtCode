#include "HDataObject.h"
#include <QObject>

using namespace He::Core;

HDataObject::HDataObject()
{
    _type = tr("[]");
}

QString HDataObject::tr(const char *sourceText, const char *comment, int n)
{
    return QObject::tr(sourceText, comment, n);
}

void HDataObject::initialize(QString type)
{
    setType(type);
}

void HDataObject::setType(QString value)
{
    value = removeBracket(value);
    _type = QChar('[') + value + QChar(']');
}

QString HDataObject::type(bool bracket) const
{
    return bracket ? _type : removeBracket(_type);
}

QString HDataObject::removeBracket(QString text) const
{
    QString str;
    str = text;
    str.remove(QChar('['));
    str.remove(QChar(']'));
    return str;
}
