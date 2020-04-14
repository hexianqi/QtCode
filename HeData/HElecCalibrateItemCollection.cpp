#include "HElecCalibrateItemCollection_p.h"
#include "IDataFactory.h"
#include "IElecCalibrateItem.h"
#include "HStreamHelper.h"
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

void HElecCalibrateItemCollection::initialize(QVariantMap param)
{
    Q_D(HElecCalibrateItemCollection);
    if (param.contains("itemClassName") && param.contains("itemTypeList"))
    {
        auto name = param.value("itemClassName").toString();
        auto types = param.value("itemTypeList").toStringList();
        for (const auto &type : types)
        {
            auto item = d->factory->createElecCalibrateItem(name);
            item->setData("[项类型]", type);
            insert(type, item);
        }
    }
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
    HStreamHelper::read<QString, HeData::IElecCalibrateItem>(s, d->datas, [=](QString type) { return d->factory->createElecCalibrateItem(type); });
}

void HElecCalibrateItemCollection::writeContent(QDataStream &s)
{
    Q_D(HElecCalibrateItemCollection);
    s << quint32(1);
    HStreamHelper::write<QString, HeData::IElecCalibrateItem>(s, d->datas);
}

HE_DATA_END_NAMESPACE
