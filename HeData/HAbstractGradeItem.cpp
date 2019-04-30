#include "HAbstractGradeItem_p.h"

HE_DATA_BEGIN_NAMESPACE

HAbstractGradeItemPrivate::HAbstractGradeItemPrivate()
{
    datas.insert("[项类型]", "Undefined");
    datas.insert("[优先级]", 1);
}

HAbstractGradeItem::HAbstractGradeItem() :
    d_ptr(new HAbstractGradeItemPrivate)
{
}

HAbstractGradeItem::HAbstractGradeItem(HAbstractGradeItemPrivate &p) :
    d_ptr(&p)
{
}

HAbstractGradeItem::~HAbstractGradeItem()
{
}

void HAbstractGradeItem::initialize(QVariantMap param)
{
    if (param.contains("datas"))
        setData(param.value("datas").toMap());
}

void HAbstractGradeItem::setData(QString name, QVariant value)
{
    d_ptr->datas.insert(name, value);
}

void HAbstractGradeItem::setData(QVariantMap value)
{
    for (auto i = value.begin(); i != value.end(); i++)
        setData(i.key(), i.value());
}

QVariant HAbstractGradeItem::data(QString name)
{
    return d_ptr->datas.value(name);
}

HE_DATA_END_NAMESPACE
