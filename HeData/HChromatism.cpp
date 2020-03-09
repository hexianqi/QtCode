#include "HChromatism_p.h"
#include "IDataFactory.h"
#include "IChromatismItem.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QPointF>

HE_DATA_BEGIN_NAMESPACE

HChromatismPrivate::HChromatismPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
}

HChromatism::HChromatism() :
    IChromatism(*new HChromatismPrivate)
{
}

HChromatism::HChromatism(HChromatismPrivate &p) :
    IChromatism(p)
{
}

HChromatism::~HChromatism()
{
}

QString HChromatism::typeName()
{
    return "HChromatism";
}

void HChromatism::readContent(QDataStream &s)
{
    Q_D(HChromatism);
    quint32 version;

    s >> version;
    HStreamHelper::read<QString, HeData::IChromatismItem>(s, d->datas, [=](QString type) { return d->factory->createChromatismItem(type); });
}

void HChromatism::writeContent(QDataStream &s)
{
    Q_D(HChromatism);
    s << quint32(1);
    HStreamHelper::write<QString, HeData::IChromatismItem>(s, d->datas);
}

double HChromatism::calcSdcm(double tc, QPointF xy)
{
    Q_D(HChromatism);
    if (!matching(tc))
        return 0.0;
    return d->selectItem->calcSdcm(xy);
}

QVariantMap HChromatism::toMap()
{
    Q_D(HChromatism);
    return d->selectItem == nullptr ? QVariantMap() : d->selectItem->data();
}

bool HChromatism::matching(double tc)
{
    Q_D(HChromatism);
    d->selectItem = nullptr;
    auto t = 65535.0;
    for (auto i : d->datas)
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
