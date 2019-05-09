#include "HAdjust_p.h"
#include "IDataFactory.h"
#include "IAdjustItem.h"
#include <QtCore/QPointF>
#include <QtCore/QDataStream>

HE_DATA_BEGIN_NAMESPACE

HAdjust::HAdjust() :
    IAdjust(*new HAdjustPrivate)
{
}

HAdjust::HAdjust(HAdjustPrivate &p) :
    IAdjust(p)
{
}

HAdjust::~HAdjust()
{
}

QString HAdjust::typeName()
{
    return "HAdjust";
}

void HAdjust::readContent(QDataStream &s, IDataFactory *f)
{
    quint32 version;
    quint32 size;
    QString key, type;

    clear();
    s >> version;
    s >> size;
    for (quint32 i = 0; i < size; i++)
    {
        s >> key >> type;
        auto item = f->createAdjustItem(type);
        item->readContent(s);
        if (s.status() != QDataStream::Ok)
        {
            clear();
            break;
        }
        insert(key, item);
    }
}

void HAdjust::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << quint32(size());
    for (auto i : keys())
    {
        s << i << item(i)->typeName();
        item(i)->writeContent(s);
    }
}

void HAdjust::restoreDefault()
{
    for (auto i : values())
        i->restoreDefault();
}

QVariantMap HAdjust::correct(QVariantMap value)
{
    QVariantMap map;
    for (auto i : keys())
    {
        if (!value.contains(i))
            continue;
        auto v = item(i)->correct(value.value(i));
        if (v.isValid())
            map.insert(i, v);
    }

    if (map.contains("[色坐标x]") && map.contains("[色坐标y]"))
        map.insert("[色坐标]", QPointF(map["[色坐标x]"].toDouble(), map["[色坐标y]"].toDouble()));
    if (map.contains("[色坐标u]") && map.contains("[色坐标v]"))
        map.insert("[色坐标uv]", QPointF(map["[色坐标u]"].toDouble(), map["[色坐标v]"].toDouble()));
    if (map.contains("[色坐标up]") && map.contains("[色坐标vp]"))
        map.insert("[色坐标uvp]", QPointF(map["[色坐标up]"].toDouble(), map["[色坐标vp]"].toDouble()));
    return map;
}

HE_DATA_END_NAMESPACE
