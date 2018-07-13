#include "HAbstractCalibrateItem_p.h"

HE_DATA_BEGIN_NAMESPACE

HAbstractCalibrateItem::HAbstractCalibrateItem()
    : d_ptr(new HAbstractCalibrateItemPrivate)
{
}

HAbstractCalibrateItem::HAbstractCalibrateItem(HAbstractCalibrateItemPrivate &p)
    : d_ptr(&p)
{
}

HAbstractCalibrateItem::~HAbstractCalibrateItem()
{
}

void HAbstractCalibrateItem::setData(QString name, QVariant value)
{
    d_ptr->datas.insert(name, value);
}

QVariant HAbstractCalibrateItem::data(QString name)
{
    return d_ptr->datas.value(name);
}

HE_DATA_END_NAMESPACE
