#include "HObject.h"
#include <QObject>

using namespace He::Core;

HObject::HObject()
{
    _type = tr("[]");
}

QString HObject::tr(const char *sourceText, const char *comment, int n)
{
    return QObject::tr(sourceText, comment, n);
}

void HObject::initialize(QString type)
{
    setType(type);
}

void HObject::setType(QString value)
{
    value = removeBracket(value);
    _type = QChar('[') + value + QChar(']');
}

QString HObject::type(bool bracket) const
{
    return bracket ? _type : removeBracket(_type);
}

QString HObject::removeBracket(QString text) const
{
    QString str;
    str = text;
    str.remove(QChar('['));
    str.remove(QChar(']'));
    return str;
}
