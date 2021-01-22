#include "HLittleProtocol_p.h"
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

HLittleProtocol::HLittleProtocol() :
    HAbstractProtocol(*new HLittleProtocolPrivate)
{
}

HLittleProtocol::HLittleProtocol(HLittleProtocolPrivate &p) :
    HAbstractProtocol(p)
{
}

HLittleProtocol::~HLittleProtocol()
{
    qDebug() << __func__;
}

QString HLittleProtocol::typeName()
{
    return "HLittleProtocol";
}

QVector<uchar> HLittleProtocol::toVector(int value)
{
    return QVector<uchar>() << uchar(value % 256) << uchar(value / 256);
}

QVector<uchar> HLittleProtocol::toVector(uint value)
{
    return QVector<uchar>() << ((value >>  0) & 0xFF)
                            << ((value >>  8) & 0xFF)
                            << ((value >> 16) & 0xFF)
                            << ((value >> 24) & 0xFF);
}

QVector<uchar> HLittleProtocol::toVector(double value)
{
    return toVector(int(value));
}

int HLittleProtocol::toInt(QVector<uchar> value)
{
    if (value.size() < 2)
        return 0;
    return value.at(0) + value.at(1) * 256;
}

uint HLittleProtocol::toUInt(QVector<uchar> value)
{
    if (value.size() < 4)
        return 0;
    return uint(value.at(0) + (value.at(1) << 8) + (value.at(2) << 16) + (value.at(3) << 24));
}

QVector<int> HLittleProtocol::toInt(QVector<uchar> value, int size)
{
    QVector<int> result;
    auto n = size == 0 ? value.size() / 2 : qMin(size, value.size() / 2);
    for (int i = 0; i < n; i++)
        result << value.at(2 * i) + value.at(2 * i + 1) * 256;
    return result;
}

QVector<uint> HLittleProtocol::toUInt(QVector<uchar> value, int size)
{
    QVector<uint> result;
    auto n = size == 0 ? value.size() / 4 : qMin(size, value.size() / 4);
    for (int i = 0; i < n; i++)
        result << uint(value.at(4 * i) + (value.at(4 * i + 1) << 8) + (value.at(4 * i + 2) << 16) + (value.at(4 * i + 3) << 24));
    return result;
}

QVector<double> HLittleProtocol::toDouble(QVector<uchar> value, int size)
{
    QVector<double> result;
    auto n = size == 0 ? value.size() / 2 : qMin(size, value.size() / 2);
    for (int i = 0; i < n; i++)
        result << value.at(2 * i) + value.at(2 * i + 1) * 256;
    return result;
}

HE_COMMUNICATE_END_NAMESPACE
