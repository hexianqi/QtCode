#include "HBigUCharConvert_p.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HBigUCharConvertPrivate::HBigUCharConvertPrivate()
{
    hashDigits.insert(QVariant::Int, 2);
    hashDigits.insert(QVariant::Double, 2);
    hashDigits.insert(QVariant::UInt, 4);
}

HBigUCharConvert::HBigUCharConvert(QObject *parent) :
    HAbstractUCharConvert(*new HBigUCharConvertPrivate, parent)
{
}

HBigUCharConvert::HBigUCharConvert(HBigUCharConvertPrivate &p, QObject *parent) :
    HAbstractUCharConvert(p, parent)
{
}

HBigUCharConvert::~HBigUCharConvert()
{
}

QString HBigUCharConvert::typeName()
{
    return "HBigUCharConvert";
}

QVector<uchar> HBigUCharConvert::toVector(int value)
{
    return QVector<uchar>() << uchar(value / 256) << uchar(value % 256);
}

QVector<uchar> HBigUCharConvert::toVector(double value)
{
    return toVector(int(value));
}

QVector<uchar> HBigUCharConvert::toVector(uint value)
{
    return QVector<uchar>() << ((value >> 24) & 0xFF)
                            << ((value >> 16) & 0xFF)
                            << ((value >>  8) & 0xFF)
                            << ((value >>  0) & 0xFF);
}

int HBigUCharConvert::toInt(QVector<uchar> data, int pos)
{
    if (data.size() < pos + 2)
        return 0;
    return data.at(pos) * 256 + data.at(pos + 1);
}

double HBigUCharConvert::toDouble(QVector<uchar> data, int pos)
{
    return toInt(data, pos);
}

uint HBigUCharConvert::toUInt(QVector<uchar> data, int pos)
{
    if (data.size() < pos + 4)
        return 0;
    return uint((data.at(pos) << 24) + (data.at(pos + 1) << 16) + (data.at(pos + 2) << 8) + data.at(pos + 3));
}

HE_END_NAMESPACE
