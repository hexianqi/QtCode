#include "HDataHelper.h"
#include <QtCore/QVector>
#include <QtCore/QSet>
#include <QtCore/QDateTime>
#include <QtCore/QPointF>

HE_BEGIN_NAMESPACE

quint16 HDataHelper::readUInt16(QVector<uchar> data, int &pos)
{
    auto v1 = data[pos++];
    auto v2 = data[pos++];
    return v1 * 256 + v2;
}

QVector<uchar> HDataHelper::writeUInt16(quint16 data)
{
    return QVector<uchar>() << uchar(data / 256) << uchar(data % 256);
}

bool HDataHelper::checkHead(const QVector<uchar> &data, int &pos, int &version)
{
    if (data.size() < pos + 4)
        return false;
    int size = readUInt16(data, pos);
    version = readUInt16(data, pos);
    return data.size() >= size + pos - 4;
}

QSet<QString> HDataHelper::supplement(QSet<QString> set, QSet<QString> other)
{
    for (const auto &s : other)
    {
        if (set.contains(s))
            return set.unite(other);
    }
    return set;
}

QVariant HDataHelper::derive(QString type, QVariantMap data)
{
    if (data.contains(type))
        return data.value(type);

    if (type == "[测量日期时间]")
    {
        if (data.contains("[测量日期]") && data.contains("[测量时间]"))
            return QDateTime(data.value("[测量日期]").toDate(), data.value("[测量时间]").toTime());
        return QDateTime::currentDateTime();
    }
    if (type == "[测量日期]")
    {
        if (data.contains("[测量日期时间]"))
            return data.value("[测量日期时间]").toDate();
        return QDate::currentDate();
    }
    if (type == "[测量时间]")
    {
        if (data.contains("[测量日期时间]"))
            return data.value("[测量日期时间]").toTime();
        return QTime::currentTime();
    }
    if (type == "[色坐标]")
    {
        if (data.contains("[色坐标x]") && data.contains("[色坐标y]"))
            return QPointF(data.value("[色坐标x]").toDouble(), data.value("[色坐标y]").toDouble());
    }
    if (type == "[色坐标uv]")
    {
        if (data.contains("[色坐标u]") && data.contains("[色坐标v]"))
            return QPointF(data.value("[色坐标u]").toDouble(), data.value("[色坐标v]").toDouble());
    }
    if (type == "[色坐标uvp]")
    {
        if (data.contains("[色坐标up]") && data.contains("[色坐标vp]"))
            return QPointF(data.value("[色坐标up]").toDouble(), data.value("[色坐标vp]").toDouble());
    }
    if (type == "[色坐标x]")
    {
        if (data.contains("[色坐标]"))
            return data.value("[色坐标]").toPointF().x();
    }
    if (type == "[色坐标y]")
    {
        if (data.contains("[色坐标]"))
            return data.value("[色坐标]").toPointF().y();
    }
    if (type == "[色坐标u]")
    {
        if (data.contains("[色坐标uv]"))
            return data.value("[色坐标uv]").toPointF().x();
    }
    if (type == "[色坐标v]")
    {
        if (data.contains("[色坐标uv]"))
            return data.value("[色坐标uv]").toPointF().y();
    }
    if (type == "[色坐标up]")
    {
        if (data.contains("[色坐标uvp]"))
            return data.value("[色坐标uvp]").toPointF().x();
    }
    if (type == "[色坐标vp]")
    {
        if (data.contains("[色坐标uvp]"))
            return data.value("[色坐标uvp]").toPointF().y();
    }
    return QVariant();
}

HE_END_NAMESPACE
