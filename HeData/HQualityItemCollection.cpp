#include "HQualityItemCollection_p.h"
#include "IDataFactory.h"
#include "IQualityItem.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"
#include <QtGui/QColor>

HE_DATA_BEGIN_NAMESPACE

HQualityItemCollectionPrivate::HQualityItemCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
}

HQualityItemCollection::HQualityItemCollection() :
    IQualityItemCollection(*new HQualityItemCollectionPrivate)
{
}

HQualityItemCollection::HQualityItemCollection(HQualityItemCollectionPrivate &p) :
    IQualityItemCollection(p)
{
}

QString HQualityItemCollection::typeName()
{
    return "HQualityItemCollection";
}

void HQualityItemCollection::readContent(QDataStream &s)
{
    Q_D(HQualityItemCollection);
    quint32 version;

    s >> version;
    HStreamHelper::read<QString, HeData::IQualityItem>(s, d->datas, [=](QString type) { return d->factory->createQualityItem(type); });
}

void HQualityItemCollection::writeContent(QDataStream &s)
{
    Q_D(HQualityItemCollection);
    s << quint32(1);
    HStreamHelper::write<QString, HeData::IQualityItem>(s, d->datas);
}

int HQualityItemCollection::check(QVariantMap value, QVariantMap *color)
{
    for (auto i : keys())
    {
        if (!value.contains(i))
            return -1;
    }
    for (auto i : keys())
    {
        QColor c;
        if (!item(i)->isContains(value.value(i), &c))
            color->insert(i, c);
    }
    return color->isEmpty() ? 0: 1;
}

double HQualityItemCollection::drift(QString type, QVariant value)
{
    if (!contains(type))
        return 0;
    return item(type)->drift(value);
}

HE_DATA_END_NAMESPACE
