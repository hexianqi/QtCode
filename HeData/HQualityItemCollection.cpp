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

HQualityItemCollection::~HQualityItemCollection()
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
    HStreamHelper::read<QString, HeData::IQualityItem>(s, d->items, [=](QString type) { return d->factory->createQualityItem(type); });
}

void HQualityItemCollection::writeContent(QDataStream &s)
{
    Q_D(HQualityItemCollection);
    s << quint32(1);
    HStreamHelper::write<QString, HeData::IQualityItem>(s, d->items);
}

bool HQualityItemCollection::isValid(QVariantMap value)
{
    for (const auto &i : keys())
    {
        if (!value.contains(i))
            return false;
    }
    return true;
}

bool HQualityItemCollection::check(QVariantMap value, QVariantMap *color)
{
    for (const auto &i : keys())
    {
        QColor c;
        if (!item(i)->isContains(value.value(i), &c))
            color->insert(i, c);
    }
    return color->isEmpty();
}

double HQualityItemCollection::drift(QString type, QVariant value)
{
    if (!contains(type))
        return 0;
    return item(type)->drift(value);
}

HE_DATA_END_NAMESPACE
