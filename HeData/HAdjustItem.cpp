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
    d_ptr(new HAdjustItemPrivate)
{
    restoreDefault();
}

HAdjustItem::HAdjustItem(HAdjustItemPrivate &p) :
    d_ptr(&p)
{
}

HAdjustItem::~HAdjustItem()
{
}

void HAdjustItem::initialize(QVariantMap param)
{
    if (param.contains("datas"))
        setData(param.value("datas").toMap());
}

QString HAdjustItem::typeName()
{
    return "HAdjustItem";
}

void HAdjustItem::setData(QString name, QVariant value)
{
    d_ptr->datas.insert(name, value);
}

void HAdjustItem::setData(QVariantMap value)
{
    for (auto i = value.begin(); i != value.end(); i++)
        setData(i.key(), i.value());
}

QVariant HAdjustItem::data(QString name)
{
    return d_ptr->datas.value(name);
}

void HAdjustItem::readContent(QDataStream &s)
{
    quint32 version;
    s >> version;
    s >> d_ptr->datas;
}

void HAdjustItem::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << d_ptr->datas;
}

void HAdjustItem::restoreDefault()
{
    auto min = toFormatInfo(data("[项类型]").toString())->min();
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
    return QStringList() << toCaption(t) << toString("[调整比率]", data("[调整比率]")) << toString(t, data("[测试值]")) << toString(t, data("[标准值]"));
}

HE_DATA_END_NAMESPACE
