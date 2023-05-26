#include "HAbstractUCharConvert_p.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HAbstractUCharConvert::HAbstractUCharConvert(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractUCharConvertPrivate)
{
}

HAbstractUCharConvert::HAbstractUCharConvert(HAbstractUCharConvertPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractUCharConvert::~HAbstractUCharConvert()
{
}

void HAbstractUCharConvert::initialize(QVariantMap /*param*/)
{

}

void HAbstractUCharConvert::setDigits(QVariant::Type type, int value)
{
    d_ptr->hashDigits.insert(type, value);
}

int HAbstractUCharConvert::digits(QVariant::Type type)
{
    return d_ptr->hashDigits.value(type, 4);
}

QVector<uchar> HAbstractUCharConvert::toUChar(uchar value)
{
    return QVector<uchar>() << value;
}

QVector<uchar> HAbstractUCharConvert::toUChar(QVariant value)
{
    if (value.type() == QVariant::Int)
        return toVector(value.toInt());
    if (value.type() == QVariant::Double)
        return toVector(value.toDouble());
    if (value.type() == QVariant::UInt)
        return toVector(value.toUInt());
    if (value.type() == QVariant::List)
        return toUChar(value.toList());
    return QVector<uchar>();
}

QVector<uchar> HAbstractUCharConvert::toUChar(QVariantList value)
{
    QVector<uchar> data;
    for (auto i : value)
        data << toUChar(i);
    return data;
}

QVariant HAbstractUCharConvert::toValue(QVariant::Type type, QVector<uchar> data, int pos)
{
    if (type == QVariant::Int)
        return toInt(data, pos);
    if (type == QVariant::Double)
        return toDouble(data, pos);
    if (type == QVariant::UInt)
        return toUInt(data, pos);
    return QVariant();
}

QVariantList HAbstractUCharConvert::toValues(QVariant::Type type, QVector<uchar> data, int size)
{
    QVariantList result;
    auto d = digits(type);
    auto n = size == 0 ? data.size() / d : qMin(size, data.size() / d);
    for (int i = 0; i < n; i++)
        result << toValue(type, data, i * d);
    return result;
}

uchar HAbstractUCharConvert::toValue(QVector<uchar> data)
{
    return data.size() > 0 ? data.first() : 0;
}

HE_END_NAMESPACE
