#include "HElecCalibrateItemCollection_p.h"
#include "IDataFactory.h"
#include "IElecCalibrateItem.h"
#include "HDataHelper.h"
#include "HeCore/HAppContext.h"

HE_DATA_BEGIN_NAMESPACE

HElecCalibrateItemCollectionPrivate::HElecCalibrateItemCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
}

HElecCalibrateItemCollection::HElecCalibrateItemCollection() :
    IElecCalibrateItemCollection(*new HElecCalibrateItemCollectionPrivate)
{
}

HElecCalibrateItemCollection::HElecCalibrateItemCollection(HElecCalibrateItemCollectionPrivate &p) :
    IElecCalibrateItemCollection(p)
{
}

HElecCalibrateItemCollection::~HElecCalibrateItemCollection()
{
}

QString HElecCalibrateItemCollection::typeName()
{
    return "HElecCalibrateItemCollection";
}

void HElecCalibrateItemCollection::readContent(QDataStream &s)
{
    Q_D(HElecCalibrateItemCollection);
    quint32 version;

    s >> version;
    HDataHelper::read<QString, HeData::IElecCalibrateItem>(s, d->datas, [=](QString type) { return d->factory->createElecCalibrateItem(type); });
}

void HElecCalibrateItemCollection::writeContent(QDataStream &s)
{
    Q_D(HElecCalibrateItemCollection);
    s << quint32(1);
    HDataHelper::write<QString, HeData::IElecCalibrateItem>(s, d->datas);
}

IElecCalibrateItem *HElecCalibrateItemCollection::itemAt(int index)
{
    if (index < 0 || index >= size())
        return nullptr;
    return values().at(index);
}

HE_DATA_END_NAMESPACE
