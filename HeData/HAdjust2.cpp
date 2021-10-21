#include "HAdjust2_p.h"
#include "IDataFactory.h"
#include "IAdjustItem.h"
#include "IAdjustItemCollection.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"

HE_DATA_BEGIN_NAMESPACE

HAdjust2Private::HAdjust2Private()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
}

HAdjust2::HAdjust2() :
    IAdjust2(*new HAdjust2Private)
{
}

HAdjust2::HAdjust2(HAdjust2Private &p) :
    IAdjust2(p)
{
}

HAdjust2::~HAdjust2()
{

}

QString HAdjust2::typeName()
{
    return "HAdjust2";
}

void HAdjust2::readContent(QDataStream &s)
{
    Q_D(HAdjust2);
    quint32 version;

    s >> version;
//    if (version == 1)
//    {
//        QMap<QString, IAdjustItem *> data;
//        HStreamHelper::read<QString, HeData::IAdjustItem>(s, data, [=](QString type) { return d->factory->createAdjustItem(type); });
//        auto item = d->factory->createAdjustItemCollection("HAdjustItemCollection");
//        for (auto it = data.begin(); it != data.end(); it++)
//            item->insert(it.key(), it.value());
//        d->items.insert("1", item);
//        return;
//    }
    HStreamHelper::read<QString, HeData::IAdjustItemCollection>(s, d->items, [=](QString type) { return d->factory->createAdjustItemCollection(type); });
}

void HAdjust2::writeContent(QDataStream &s)
{
    Q_D(HAdjust2);
    s << quint32(2);
    HStreamHelper::write<QString, HeData::IAdjustItemCollection>(s, d->items);
}

void HAdjust2::restoreDefault()
{
    for (auto i : values())
        i->restoreDefault();
}

QVariantMap HAdjust2::correct(double tc, QVariantMap value)
{
    Q_D(HAdjust2);
    if (!matching(tc))
        return QVariantMap();
    return d->selectItem->correct(value);
}

bool HAdjust2::matching(double tc)
{
    Q_D(HAdjust2);
    d->selectItem = nullptr;
    auto t = 65535.0;
    for (auto i : d->items)
    {
        if (!i->data("[使用]").toBool())
            continue;
        auto v = qAbs(i->data("[相关色温]").toDouble() - tc);
        if (v < t)
        {
            t = v;
            d->selectItem = i;
        }
    }
    return d->selectItem != nullptr;
}

HE_DATA_END_NAMESPACE
