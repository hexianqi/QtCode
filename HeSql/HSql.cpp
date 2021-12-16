#include "HSql.h"
#include "HeCore/HCore.h"
#include "HeData/ITestData.h"
#include <QtCore/QDateTime>
#include <QtGui/QPolygonF>
#include <QtSql/QSqlRecord>

HE_BEGIN_NAMESPACE

QPolygonF toPolygonF(QString value)
{
    QPolygonF poly;
    auto list = value.split(",", QString::SkipEmptyParts);
    if (list.isEmpty())
        return poly;
    for (const auto &t : list)
    {
        auto l = t.split(":", QString::SkipEmptyParts);
        if (l.size() < 2)
            continue;
        poly << QPointF(l[0].toDouble(), l[1].toDouble());
    }
    return poly;
}

QString fromPolygonF(QPolygonF value)
{
    QStringList list;
    for (auto p : value)
        list << HCore::toString("[波长]", p.x()) + ":" +  HCore::toString("[光谱能量百分比]", p.y());
    return list.join(",");
}

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
    for (const auto &f : field)
    {
        if (f == "ID")
            continue;
        auto value = data->data(toType(f));
        if (value.isValid())
        {
            if (f == "EnergyGraph")
                value = fromPolygonF(value.value<QPolygonF>());
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
    for (const auto &t : type)
    {
        auto field = toField(t);
        auto value = record.value(field);
        if (value.isValid())
        {
            if (field == "EnergyGraph")
                value = toPolygonF(value.toString());
        }
        result.insert(t, value);
    }
    return result;
}

HE_END_NAMESPACE
