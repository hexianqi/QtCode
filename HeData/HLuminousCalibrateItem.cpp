#include "HLuminousCalibrateItem_p.h"
#include "HeAlgorithm/HMath.h"
#include <QtGui/QPolygonF>
#include <QtCore/QDataStream>

HE_BEGIN_NAMESPACE

HLuminousCalibrateItemPrivate::HLuminousCalibrateItemPrivate()
{
    datas.insert("[项类型]", "Undefined");
}

HLuminousCalibrateItem::HLuminousCalibrateItem() :
    HAbstractDataItem(*new HLuminousCalibrateItemPrivate)
{
    setTotalGears(5);
}

HLuminousCalibrateItem::HLuminousCalibrateItem(HLuminousCalibrateItemPrivate &p) :
    HAbstractDataItem(p)
{
}

HLuminousCalibrateItem::~HLuminousCalibrateItem()
{
}

QString HLuminousCalibrateItem::typeName()
{
    return "HLuminousCalibrateItem";
}

void HLuminousCalibrateItem::readContent(QDataStream &s)
{
    Q_D(HLuminousCalibrateItem);
    quint32 version;
    d->relations.clear();
    s >> version;
    s >> d->datas;
    s >> d->relations;
}

void HLuminousCalibrateItem::writeContent(QDataStream &s)
{
    Q_D(HLuminousCalibrateItem);
    s << quint32(1);
    s << d->datas;
    s << d->relations;
}

void HLuminousCalibrateItem::setTotalGears(int value)
{
    Q_D(HLuminousCalibrateItem);
    if (value == d->relations.size())
        return;

    d->relations.clear();
    for (int i = 0; i < value; i++)
        d->relations.append(QPolygonF() << QPointF(0, 10) << QPointF(60000, 10000));
}

int HLuminousCalibrateItem::totalGears()
{
    Q_D(HLuminousCalibrateItem);
    return d->relations.size();
}

void HLuminousCalibrateItem::setRelation(int index, QPolygonF value)
{
    Q_D(HLuminousCalibrateItem);
    if (index < 0 || index >= d->relations.size() || value.size() < 2)
        return;
    d->relations[index] = value;
}

QPolygonF HLuminousCalibrateItem::relation(int index)
{
    Q_D(HLuminousCalibrateItem);
    if (index < 0 || index >= d->relations.size())
        return {};
    return d->relations.at(index);
}

double HLuminousCalibrateItem::toReal(double value, int index)
{
    Q_D(HLuminousCalibrateItem);
    if (index < 0 || index >= d->relations.size())
        return 0.0;
    return HMath::interpolate(value, d->relations.at(index));
}

HE_END_NAMESPACE
