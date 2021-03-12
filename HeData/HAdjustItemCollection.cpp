#include "HAdjustItemCollection_p.h"
#include "IDataFactory.h"
#include "IAdjustItem.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"

HE_DATA_BEGIN_NAMESPACE

HAdjustItemCollectionPrivate::HAdjustItemCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    datas.insert("[使用]", true);
    datas.insert("[相关色温]", 3000.0);
}

HAdjustItemCollection::HAdjustItemCollection() :
    IAdjustItemCollection(*new HAdjustItemCollectionPrivate)
{
}

HAdjustItemCollection::HAdjustItemCollection(HAdjustItemCollectionPrivate &p) :
    IAdjustItemCollection(p)
{
}

QString HAdjustItemCollection::typeName()
{
    return "HAdjustItemCollection";
}

void HAdjustItemCollection::readContent(QDataStream &s)
{
    Q_D(HAdjustItemCollection);
    quint32 version;

    s >> version;
    HStreamHelper::read<QString, HeData::IAdjustItem>(s, d->items, [=](QString type) { return d->factory->createAdjustItem(type); });
    s >> d->datas;
}

void HAdjustItemCollection::writeContent(QDataStream &s)
{
    Q_D(HAdjustItemCollection);
    s << quint32(1);
    HStreamHelper::write<QString, HeData::IAdjustItem>(s, d->items);
    s << d->datas;
}

void HAdjustItemCollection::setData(QString name, QVariant value)
{
    Q_D(HAdjustItemCollection);
    d->datas.insert(name, value);
}

QVariant HAdjustItemCollection::data(QString name)
{
    Q_D(HAdjustItemCollection);
    return d->datas.value(name);
}

void HAdjustItemCollection::restoreDefault()
{
    setData("[使用]", true);
    setData("[相关色温]", 3000.0);
    for (auto i : values())
        i->restoreDefault();
}

QVariantMap HAdjustItemCollection::correct(QVariantMap value)
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
    return map;
}

HE_DATA_END_NAMESPACE
