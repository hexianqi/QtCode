#include "HBigProtocol_p.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HBigProtocol::HBigProtocol() :
    HAbstractProtocol(*new HBigProtocolPrivate)
{
}

HBigProtocol::HBigProtocol(HBigProtocolPrivate &p) :
    HAbstractProtocol(p)
{
}

HBigProtocol::~HBigProtocol() = default;

QString HBigProtocol::typeName()
{
    return "HBigProtocol";
}

QVector<uchar> HBigProtocol::toVector(int value)
{
    return QVector<uchar>() << uchar(value / 256) << uchar(value % 256);
}

QVector<uchar> HBigProtocol::toVector(uint value)
{
    return QVector<uchar>() << ((value >> 24) & 0xFF)
                            << ((value >> 16) & 0xFF)
                            << ((value >>  8) & 0xFF)
                            << ((value >>  0) & 0xFF);
}

QVector<uchar> HBigProtocol::toVector(double value)
{
    return toVector(int(value));
}

int HBigProtocol::toInt(QVector<uchar> value)
{
    if (value.size() < 2)
        return 0;
    return value.at(0) * 256 + value.at(1);
}

uint HBigProtocol::toUInt(QVector<uchar> value)
{
    if (value.size() < 4)
        return 0;
    return uint((value.at(0) << 24) + (value.at(1) << 16) + (value.at(2) << 8) + value.at(3));
}

QVector<int> HBigProtocol::toInt(QVector<uchar> value, int size)
{
    QVector<int> result;
    auto n = size == 0 ? value.size() / 2 : qMin(size, value.size() / 2);
    for (int i = 0; i < n; i++)
        result << value.at(2 * i) * 256 + value.at(2 * i + 1);
    return result;
}

QVector<uint> HBigProtocol::toUInt(QVector<uchar> value, int size)
{
    QVector<uint> result;
    auto n = size == 0 ? value.size() / 4 : qMin(size, value.size() / 4);
    for (int i = 0; i < n; i++)
        result << uint((value.at(4 * i) << 24) + (value.at(4 * i + 1) << 16) + (value.at(4 * i + 2) << 8) + value.at(4 * i + 3));
    return result;
}

QVector<double> HBigProtocol::toDouble(QVector<uchar> value, int size)
{
    QVector<double> result;
    auto n = size == 0 ? value.size() / 2 : qMin(size, value.size() / 2);
    for (int i = 0; i < n; i++)
        result << value.at(2 * i) * 256 + value.at(2 * i + 1);
    return result;
}

HE_END_NAMESPACE
