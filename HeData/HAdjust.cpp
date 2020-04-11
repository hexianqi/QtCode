#include "HAdjust_p.h"
#include "IDataFactory.h"
#include "IAdjustItem.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QPointF>

HE_DATA_BEGIN_NAMESPACE

HAdjustPrivate::HAdjustPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
}

HAdjust::HAdjust() :
    IAdjust(*new HAdjustPrivate)
{
}

HAdjust::HAdjust(HAdjustPrivate &p) :
    IAdjust(p)
{
}

QString HAdjust::typeName()
{
    return "HAdjust";
}

void HAdjust::readContent(QDataStream &s)
{
    Q_D(HAdjust);
    quint32 version;

    s >> version;
    HStreamHelper::read<QString, HeData::IAdjustItem>(s, d->datas, [=](QString type) { return d->factory->createAdjustItem(type); });
}

void HAdjust::writeContent(QDataStream &s)
{
    Q_D(HAdjust);
    s << quint32(1);
    HStreamHelper::write<QString, HeData::IAdjustItem>(s, d->datas);
}

void HAdjust::restoreDefault()
{
    for (auto i : values())
        i->restoreDefault();
}

QVariantMap HAdjust::correct(QVariantMap value)
{
    QVariantMap map;
    for (const auto &i : keys())
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
