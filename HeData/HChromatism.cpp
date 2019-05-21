#include "HChromatism_p.h"
#include "IDataFactory.h"
#include "IChromatismItem.h"
#include <QtCore/QPointF>
#include <QtCore/QJsonObject>
#include <QtCore/QDataStream>

HE_DATA_BEGIN_NAMESPACE

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

void HChromatism::readContent(QDataStream &s, IDataFactory *f)
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
        auto item = f->createChromatismItem(type);
        item->readContent(s);
        if (s.status() != QDataStream::Ok)
        {
            clear();
            break;
        }
        insert(key, item);
    }
}

void HChromatism::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << quint32(size());
    for (auto i : keys())
    {
        s << i << item(i)->typeName();
        item(i)->writeContent(s);
    }
}

double HChromatism::calcSdcm(double tc, QPointF xy)
{
    Q_D(HChromatism);
    if (!matching(tc))
        return 0.0;
    return d->selectItem->calcSdcm(xy);
}

QJsonObject HChromatism::toJson()
{
    Q_D(HChromatism);
    return d->selectItem == nullptr ? QJsonObject() : d->selectItem->toJson();
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


