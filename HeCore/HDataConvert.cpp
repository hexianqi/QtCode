#include "HDataConvert.h"
#include "HCore.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QRegularExpression>
#include <QtGui/QPolygonF>

HE_BEGIN_NAMESPACE

QString HDataConvert::toJson(QVariantMap value)
{
    auto obj = QJsonObject::fromVariantMap(value);
    auto doc = QJsonDocument(obj);
    return doc.toJson(QJsonDocument::Compact);
}

QVariantMap HDataConvert::fromJson(QString value)
{
    auto doc = QJsonDocument::fromJson(value.toUtf8());
    if (doc.isObject())
        return doc.object().toVariantMap();
    return {};
}

QString HDataConvert::toString(const QString &type, const QList<double> &value)
{
    return HCore::toString(type, value).join(" ");
}

QList<double> HDataConvert::toList(QString value)
{
    auto text = value.split(QRegularExpression("[\\s,]"), QString::SkipEmptyParts);
    if (text.isEmpty())
        return {};

    QList<double> result;
    for (const auto &t : text)
        result << t.toDouble();
    return result;
}

QString HDataConvert::toString(const QPolygonF &value, int precX, int precY)
{
    QStringList list;
    for (auto p : value)
        list << QString("%1:%2").arg(p.x(), 0, 'f', precX).arg(p.y(), 0, 'f', precY);
    return list.join(",");
}

QPolygonF HDataConvert::toPolygonF(QString value)
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

int HDataConvert::strHexToDecimal(const QString &text)
{
    bool ok;
    return text.toInt(&ok, 16);
}

int HDataConvert::strDecimalToDecimal(const QString &text)
{
    bool ok;
    return text.toInt(&ok, 10);
}

int HDataConvert::strBinToDecimal(const QString &text)
{
    bool ok;
    return text.toInt(&ok, 2);
}

QString HDataConvert::strHexToStrBin(const QString &text, int fieldWidth)
{
    auto decimal = strHexToDecimal(text);
    return QString("%1").arg(decimal, fieldWidth, 2, QChar('0'));
}

QString HDataConvert::decimalToStrBin(int decimal, int fieldWidth)
{
    return QString("%1").arg(decimal, fieldWidth, 2, QChar('0'));
}

QString HDataConvert::decimalToStrHex(int decimal, int fieldWidth)
{
    return QString("%1").arg(decimal, fieldWidth, 16, QChar('0'));
}

QByteArray HDataConvert::toByteArray(int value)
{
    QByteArray result;
    result.resize(4);
    result[3] = (uchar)((0x000000FF & value) >> 0);
    result[2] = (uchar)((0x0000FF00 & value) >> 8);
    result[1] = (uchar)((0x00FF0000 & value) >> 16);
    result[0] = (uchar)((0xFF000000 & value) >> 24);
    return result;
}

QByteArray HDataConvert::toByteArrayRec(int value)
{
    QByteArray result;
    result.resize(4);
    result[0] = (uchar)((0x000000FF & value) >> 0);
    result[1] = (uchar)((0x0000FF00 & value) >> 8);
    result[2] = (uchar)((0x00FF0000 & value) >> 16);
    result[3] = (uchar)((0xFF000000 & value) >> 24);
    return result;
}

QByteArray HDataConvert::toByteArray(ushort value)
{
    QByteArray result;
    result.resize(2);
    result[1] = (uchar)((0x00FF & value) >> 0);
    result[0] = (uchar)((0xFF00 & value) >> 8);
    return result;
}

QByteArray HDataConvert::toByteArrayRec(ushort value)
{
    QByteArray result;
    result.resize(2);
    result[0] = (uchar)((0x00FF & value) >> 0);
    result[1] = (uchar)((0xFF00 & value) >> 8);
    return result;
}

int HDataConvert::toInt(const QByteArray &value)
{
    int i = 0;
    i |= (0x000000FF & (value.at(3) << 0));
    i |= (0x0000FF00 & (value.at(2) << 8));
    i |= (0x00FF0000 & (value.at(1) << 16));
    i |= (0xFF000000 & (value.at(0) << 24));
    return i;
}

int HDataConvert::toIntRec(const QByteArray &value)
{
    int i = 0;
    i |= (0x000000FF & (value.at(0) << 0));
    i |= (0x0000FF00 & (value.at(1) << 8));
    i |= (0x00FF0000 & (value.at(2) << 16));
    i |= (0xFF000000 & (value.at(3) << 24));
    return i;
}

quint32 HDataConvert::toUInt(const QByteArray &value)
{
    quint32 i = 0;
    i |= (0x000000FF & (value.at(3) << 0));
    i |= (0x0000FF00 & (value.at(2) << 8));
    i |= (0x00FF0000 & (value.at(1) << 16));
    i |= (0xFF000000 & (value.at(0) << 24));
    return i;
}

quint32 HDataConvert::toUIntRec(const QByteArray &value)
{
    quint32 i = 0;
    i |= (0x000000FF & (value.at(0) << 0));
    i |= (0x0000FF00 & (value.at(1) << 8));
    i |= (0x00FF0000 & (value.at(2) << 16));
    i |= (0xFF000000 & (value.at(3) << 24));
    return i;
}

ushort HDataConvert::toUShort(const QByteArray &value)
{
    ushort i = 0;
    i |= (0x00FF & (value.at(1) << 0));
    i |= (0xFF00 & (value.at(0) << 8));
    return i;
}

ushort HDataConvert::toUShortRec(const QByteArray &value)
{
    ushort i = 0;
    i |= (0x00FF & (value.at(0) << 0));
    i |= (0xFF00 & (value.at(1) << 8));
    return i;
}

HE_END_NAMESPACE
