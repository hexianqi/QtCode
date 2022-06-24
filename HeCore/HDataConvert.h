#pragma once

#include "HNamespace.h"
#include <QtCore/QVariant>

HE_BEGIN_NAMESPACE

class HDataConvert
{
public:
    // Json格式
    static QString toJson(QVariantMap);
    static QVariantMap fromJson(QString);
    // List格式
    static QString toString(const QString &type, const QList<double> &value);
    static QList<double> toList(QString value);
    // Polygon格式
    static QString toString(const QPolygonF &value, int precX = 6, int precY = 6);
    static QPolygonF toPolygonF(QString value);

public:
    // 16进制字符串转10进制
    static int strHexToDecimal(const QString &);
    // 10进制字符串转10进制
    static int strDecimalToDecimal(const QString &);
    //  2进制字符串转10进制
    static int strBinToDecimal(const QString &);
    // 16进制字符串转2进制字符串
    static QString strHexToStrBin(const QString &, int fieldWidth = 0);
    // 10进制转2进制字符串
    static QString decimalToStrBin(int, int fieldWidth = 0);
    // 10进制转16进制字符串
    static QString decimalToStrHex(int, int fieldWidth = 0);

public:
    // QByteArray
    static QByteArray toByteArray(int);
    static QByteArray toByteArrayRec(int);
    static QByteArray toByteArray(ushort);
    static QByteArray toByteArrayRec(ushort);
    static int toInt(const QByteArray &);
    static int toIntRec(const QByteArray &);
    static quint32 toUInt(const QByteArray &);
    static quint32 toUIntRec(const QByteArray &);
    static ushort toUShort(const QByteArray &);
    static ushort toUShortRec(const QByteArray &);
};

HE_END_NAMESPACE


