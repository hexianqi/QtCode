#include "HSql.h"
#include "HeCore/HCore.h"
#include "HeCore/HDataConvert.h"
#include "HeData/ITestData.h"
#include <QtCore/QDateTime>
#include <QtGui/QPolygonF>
#include <QtSql/QSqlRecord>

HE_BEGIN_NAMESPACE

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

QVariantMap HSql::toRecord(const QStringList &field, ITestData *data)
{
    QVariantMap result;
    auto jfield = membership("|Json格式|");
    auto lfield = membership("|列表格式|");
    auto p02field = membership("|多边形格式_02|");
    auto p11field = membership("|多边形格式_11|");

    for (const auto &f : field)
    {
        if (f == "ID")
            continue;
        auto type = toType(f);
        auto value = data->data(type);
        if (value.isValid())
        {
            if (jfield.contains(f))
                value = HDataConvert::toJson(value.toMap());
            else if (lfield.contains(f))
                value = HDataConvert::toString(type, value.value<QList<double>>());
            else if (p02field.contains(f))
                value = HDataConvert::toString(value.value<QPolygonF>(), 0, 2);
            else if (p11field.contains(f))
                value = HDataConvert::toString(value.value<QPolygonF>(), 1, 1);
        }
        else if (f == "TestDateTime")
            value = QDateTime::currentDateTime();
        else if (f == "TestDate")
            value = QDate::currentDate();
        else if (f == "TestTime")
            value = QTime::currentTime();
        result.insert(f, value);
    }
    return result;
}

QVariantMap HSql::toData(const QStringList &type, QSqlRecord record)
{
    QVariantMap result;
    auto jfield = membership("|Json格式|");
    auto lfield = membership("|列表格式|");
    auto p02field = membership("|多边形格式_02|");
    auto p11field = membership("|多边形格式_11|");

    for (const auto &t : type)
    {
        auto field = toField(t);
        auto value = record.value(field);
        if (value.isValid())
        {
            if (jfield.contains(field))
                value = HDataConvert::fromJson(value.toString());
            else if (lfield.contains(field))
                value = QVariant::fromValue<QList<double>>(HDataConvert::toList(value.toString()));
            else if (p02field.contains(field) || p11field.contains(field))
                value = HDataConvert::toPolygonF(value.toString());
        }
        result.insert(t, value);
    }
    return result;
}

QStringList HSql::generateFieldFind(const QString name, const QStringList &field)
{
    auto list = field;
    auto surplus = QStringList() << "ID" << membership(QStringList() << "|Json格式|" << "|列表格式|" << "|多边形格式_02|" << "|多边形格式_11|");
    if (name == "Spec")
        surplus << "Rx";
    for (auto v : surplus)
        list.removeAll(v);
    return list;
}

QStringList HSql::removeFieldGraph(const QStringList &field)
{
    auto list = field;
    auto surplus = QStringList() << "ID" << membership(QStringList() << "|Json格式|" << "|多边形格式_02|" << "|多边形格式_11|");
    for (auto v : surplus)
        list.removeAll(v);
    return list;
}

HE_END_NAMESPACE
