#include "HTestData_p.h"

HE_CONTROLLER_BEGIN_NAMESPACE

void HTestDataPrivate::setData(QString type, QVariant value)
{
    if (datas.contains(type))
    {
        datas[type] = value;
        return;
    }
    if (successor != nullptr)
        return successor->setData(type, value);
    addData(type, value);
}

void HTestDataPrivate::addData(QString type, QVariant value)
{
    datas.insert(type, value);
}

QVariant HTestDataPrivate::data(QString type)
{
    if (datas.contains(type))
        return datas.value(type);
    if (successor != nullptr)
        return successor->data(type);
    return QVariant();
}

HTestData::HTestData()
    : d_ptr(new HTestDataPrivate)
{
}

HTestData::~HTestData()
{
}

HTestData::HTestData(HTestDataPrivate &p)
    : d_ptr(&p)
{
}


void HTestData::initialize(QVariantMap param)
{
    if (param.contains("successor"))
        d_ptr->successor = FromVariant(ITestData, param.value("successor"));
    if (param.contains("datas"))
    {
        QHashIterator<QString, QVariant> i(param.value("datas").toHash());
        while (i.hasNext())
        {
            i.next();
            d_ptr->addData(i.key(), i.value());
        }
    }
}

void HTestData::setSuccessor(ITestData *successor)
{
    d_ptr->successor = successor;
}

void HTestData::setData(QString type, QVariant value)
{
     d_ptr->setData(type, value);
}

QVariant HTestData::data(QString type)
{
    return d_ptr->data(type);
}

HE_CONTROLLER_END_NAMESPACE
