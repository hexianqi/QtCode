#include "HAbstractDataItem_p.h"

HE_DATA_BEGIN_NAMESPACE

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
    {
        QMapIterator<QString, QVariant> i(param.value("datas").toMap());
        while (i.hasNext())
        {
            i.next();
            setData(i.key(), i.value());
        }
    }
}

void HAbstractDataItem::setData(QString name, QVariant value)
{
    d_ptr->datas.insert(name, value);
}

QVariant HAbstractDataItem::data(QString name)
{
    return d_ptr->datas.value(name);
}

HE_DATA_END_NAMESPACE
