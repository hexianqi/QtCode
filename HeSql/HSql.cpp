#include "HSql.h"
#include "HeCore/HCore.h"
#include <QtCore/QVariant>

HE_SQL_BEGIN_NAMESPACE

QString toString(QString field, QVariant value)
{
    return HeCore::toString(toType(field), value);
}

QString toCaptionUnit(QString field)
{
    return HeCore::toCaptionUnit(toType(field));
}

HE_SQL_END_NAMESPACE
