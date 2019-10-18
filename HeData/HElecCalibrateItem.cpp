#include "HElecCalibrateItem_p.h"
#include "HeAlgorithm/HMath.h"
#include <QtCore/QDataStream>

HE_ALGORITHM_USE_NAMESPACE
HE_DATA_BEGIN_NAMESPACE

HElecCalibrateItemPrivate::HElecCalibrateItemPrivate()
{
    datas.insert("[项类型]", "Undefined");
}

HElecCalibrateItem::HElecCalibrateItem() :
    IElecCalibrateItem(*new HElecCalibrateItemPrivate)
{
    restoreDefault();
}

HElecCalibrateItem::HElecCalibrateItem(HElecCalibrateItemPrivate &p) :
    IElecCalibrateItem(p)
{
}

HElecCalibrateItem::~HElecCalibrateItem()
{
}

QString HElecCalibrateItem::typeName()
{
    return "HElecCalibrateItem";
}

void HElecCalibrateItem::readContent(QDataStream &s)
{
    Q_D(HElecCalibrateItem);
    quint32 version;
    d->relation.clear();
    s >> version;
    s >> d->datas;
    s >> d->relation;
}

void HElecCalibrateItem::writeContent(QDataStream &s)
{
    Q_D(HElecCalibrateItem);
    s << quint32(1);
    s << d->datas;
    s << d->relation;
}

void HElecCalibrateItem::setRelation(QPolygonF value)
{
    Q_D(HElecCalibrateItem);
    d->relation = value;
}

QPolygonF HElecCalibrateItem::relation()
{
    Q_D(HElecCalibrateItem);
    return d->relation;
}

double HElecCalibrateItem::toFiction(double value)
{
    Q_D(HElecCalibrateItem);
    return HMath::interpolateY(value, d->relation);
}

double HElecCalibrateItem::toReal(double value)
{
    Q_D(HElecCalibrateItem);
    return HMath::interpolate(value, d->relation);
}

void HElecCalibrateItem::restoreDefault()
{
    Q_D(HElecCalibrateItem);
    d->relation.clear();
    d->relation = QPolygonF() << QPointF(0, 10) << QPointF(6000, 100);
}

HE_DATA_END_NAMESPACE
