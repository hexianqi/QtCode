#include "HAbstractDataItem_p.h"

HE_BEGIN_NAMESPACE

HAbstractDataItem::HAbstractDataItem() :
    d_ptr(new HAbstractDataItemPrivate)
{
}

HAbstractDataItem::HAbstractDataItem(HAbstractDataItemPrivate &p) :
    d_ptr(&p)
{
}

HAbstractDataItem::~HAbstractDataItem()
{
}

void HAbstractDataItem::initialize(QVariantMap param)
{
    if (param.contains("datas"))
        setData(param.value("datas").toMap());
}

void HAbstractDataItem::setData(QString name, QVariant value)
{
    if (d_ptr->datas.value(name) != value)
    {
        d_ptr->datas.insert(name, value);
        d_ptr->modified = true;
    }
}

void HAbstractDataItem::setData(QVariantMap value)
{
    for (auto i = value.begin(); i != value.end(); i++)
        setData(i.key(), i.value());
}

QVariant HAbstractDataItem::data(QString name)
{
    return d_ptr->datas.value(name);
}

QVariantMap HAbstractDataItem::data()
{
    return d_ptr->datas;
}

HE_END_NAMESPACE
