#include "HLittleUCharConvert_p.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HLittleUCharConvertPrivate::HLittleUCharConvertPrivate()
{
    hashDigits.insert(QVariant::Int, 2);
    hashDigits.insert(QVariant::Double, 2);
    hashDigits.insert(QVariant::UInt, 4);
}

HLittleUCharConvert::HLittleUCharConvert(QObject *parent) :
    HAbstractUCharConvert(*new HLittleUCharConvertPrivate, parent)
{
}

HLittleUCharConvert::HLittleUCharConvert(HLittleUCharConvertPrivate &p, QObject *parent) :
    HAbstractUCharConvert(p, parent)
{
}

HLittleUCharConvert::~HLittleUCharConvert()
{
}

QString HLittleUCharConvert::typeName()
{
    return "HLittleUCharConvert";
}

QVector<uchar> HLittleUCharConvert::toVector(int value)
{
    return QVector<uchar>() << uchar(value % 256) << uchar(value / 256);
}

QVector<uchar> HLittleUCharConvert::toVector(double value)
{
    return toVector(int(value));
}

QVector<uchar> HLittleUCharConvert::toVector(uint value)
{
    return QVector<uchar>() << ((value >>  0) & 0xFF)
                            << ((value >>  8) & 0xFF)
                            << ((value >> 16) & 0xFF)
                            << ((value >> 24) & 0xFF);
}

int HLittleUCharConvert::toInt(QVector<uchar> data, int pos)
{
    if (data.size() < pos + 2)
        return 0;
    return data.at(pos) + data.at(pos + 1) * 256 ;
}

double HLittleUCharConvert::toDouble(QVector<uchar> data, int pos)
{
    return toInt(data, pos);
}

uint HLittleUCharConvert::toUInt(QVector<uchar> data, int pos)
{
    if (data.size() < pos + 4)
        return 0;
    return uint(data.at(pos) + (data.at(pos + 1) << 8) + (data.at(pos + 2) << 16) + (data.at(pos + 3) << 24));
}

HE_END_NAMESPACE
