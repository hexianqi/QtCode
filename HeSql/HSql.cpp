#include "HSql.h"
#include "HeCore/HCore.h"
#include <QtCore/QVariant>

HE_CORE_USE_NAMESPACE
HE_SQL_BEGIN_NAMESPACE

QString HSql::toString(const QString &field, const QVariant& value)
{
    return HCore::toString(toType(field), value);
}

QString HSql::toCaption(const QString &field)
{
    return HCore::toCaption(toType(field));
}

QStringList HSql::toCaption(const QStringList &field)
{
    return HCore::toCaption(toType(field));
}

QString HSql::toUnit(const QString &field)
{
    return HCore::toUnit(toType(field));
}

QString HSql::toCaptionUnit(const QString &field)
{
    return HCore::toCaptionUnit(toType(field));
}

QStringList HSql::toCaptionUnit(const QStringList &field)
{
    return HCore::toCaptionUnit(toType(field));
}

HE_SQL_END_NAMESPACE
