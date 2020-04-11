#include "HAdjustItem_p.h"
#include "HeCore/HCore.h"
#include "HeCore/HDataFormatInfo.h"
#include <QtCore/QDataStream>

HE_DATA_BEGIN_NAMESPACE

HAdjustItemPrivate::HAdjustItemPrivate()
{
    datas.insert("[项类型]", "Undefined");
}

HAdjustItem::HAdjustItem() :
    IAdjustItem(*new HAdjustItemPrivate)
{
    restoreDefault();
}

HAdjustItem::HAdjustItem(HAdjustItemPrivate &p) :
    IAdjustItem(p)
{
}

QString HAdjustItem::typeName()
{
    return "HAdjustItem";
}

void HAdjustItem::readContent(QDataStream &s)
{
    Q_D(HAdjustItem);
    quint32 version;
    s >> version;
    s >> d->datas;
}

void HAdjustItem::writeContent(QDataStream &s)
{
    Q_D(HAdjustItem);
    s << quint32(1);
    s << d->datas;
}

void HAdjustItem::restoreDefault()
{
    auto min = HCore::toFormatInfo(data("[项类型]").toString())->min();
    setData("[测试值]", min);
    setData("[标准值]", min);
    setData("[调整比率]", 100);
}

QVariant HAdjustItem::correct(QVariant value)
{
    if (!value.canConvert<double>())
        return QVariant();
    auto r = data("[调整比率]").toDouble();
    return value.toDouble() * r / 100;
}

QStringList HAdjustItem::toStringList()
{
    auto t = data("[项类型]").toString();
    return QStringList() << HCore::toCaption(t)
                         << HCore::toString("[调整比率]", data("[调整比率]"))
                         << HCore::toString(t, data("[测试值]"))
                         << HCore::toString(t, data("[标准值]"));
}

HE_DATA_END_NAMESPACE
