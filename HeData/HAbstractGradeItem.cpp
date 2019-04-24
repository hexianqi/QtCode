#include "HAbstractGradeItem_p.h"

HE_DATA_BEGIN_NAMESPACE

HAbstractGradeItemPrivate::HAbstractGradeItemPrivate()
{
    datas.insert("[优先级]", 1);
    datas.insert("[项类型]", "Undefined");
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
    {
        QMapIterator<QString, QVariant> i(param.value("datas").toMap());
        while (i.hasNext())
        {
            i.next();
            setData(i.key(), i.value());
        }
    }
}

void HAbstractGradeItem::setData(QString name, QVariant value)
{
    d_ptr->datas.insert(name, value);
}

QVariant HAbstractGradeItem::data(QString name)
{
    return d_ptr->datas.value(name);
}



HE_DATA_END_NAMESPACE
