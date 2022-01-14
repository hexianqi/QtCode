#include "HSql.h"
#include "HeCore/HCore.h"
#include "HeData/ITestData.h"
#include <QtCore/QDateTime>
#include <QtCore/QRegularExpression>
#include <QtGui/QPolygonF>
#include <QtSql/QSqlRecord>

HE_BEGIN_NAMESPACE

QStringList polygonField()
{
    return QStringList() << "EnergyGraph" << "ReflectGraph";
}

QStringList listField()
{
    return QStringList() << "TM30_Rfi" << "TM30_hj_Rf" << "TM30_hj_Rcs" << "TM30_hj_Rhs"
                         << "TM30_hj_at" << "TM30_hj_bt" << "TM30_hj_ar" << "TM30_hj_br"
                         << "TM30_hj_atn" << "TM30_hj_btn" << "TM30_hj_arn" << "TM30_hj_arn";
}

QString format(const QPolygonF &value)
{
    QStringList list;
    for (auto p : value)
        list << HCore::toString("[波长]", p.x()) + ":" +  HCore::toString("[光谱能量百分比]", p.y());
    return list.join(",");
}

QString format(const QString &type, const QList<double> &value)
{
    QStringList list;
    for (const auto &v : value)
        list << HCore::toString(type, v);
    return list.join(",");
}

QPolygonF toPolygonF(QString value)
{
    auto text = value.split(QRegularExpression("[\\s,]"), QString::SkipEmptyParts);
    if (text.isEmpty())
        return {};

    QPolygonF poly;
    for (const auto &t : text)
    {
        auto l = t.split(":", QString::SkipEmptyParts);
        if (l.size() < 2)
            continue;
        poly << QPointF(l[0].toDouble(), l[1].toDouble());
    }
    return poly;
}

QList<double> toList(QString value)
{
    auto text = value.split(QRegularExpression("[\\s,]"), QString::SkipEmptyParts);
    if (text.isEmpty())
        return {};

    QList<double> result;
    for (const auto &t : text)
        result << t.toDouble();
    return result;
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
    auto pfield = polygonField();
    auto lfield = listField();
    for (const auto &f : field)
    {
        if (f == "ID")
            continue;
        auto type = toType(f);
        auto value = data->data(type);
        if (value.isValid())
        {
            if (pfield.contains(f))
                value = format(value.value<QPolygonF>());
            else if (lfield.contains(f))
                value = format(type, value.value<QList<double>>());
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
    auto pfield = polygonField();
    auto lfield = listField();
    for (const auto &t : type)
    {
        auto field = toField(t);
        auto value = record.value(field);
        if (value.isValid())
        {
            if (pfield.contains(field))
                value = toPolygonF(value.toString());
            else if (lfield.contains(field))
                value = QVariant::fromValue<QList<double>>(toList(value.toString()));
        }
        result.insert(t, value);
    }
    return result;
}

HE_END_NAMESPACE
