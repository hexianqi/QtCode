#include "HMemento_p.h"
#include "IModel.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include <QtCore/QDataStream>

HE_BEGIN_NAMESPACE

HMementoPrivate::HMementoPrivate()
{
    model = HAppContext::getContextPointer<IModel>("IModel");
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
}

HMemento::HMemento(QObject *parent) :
    QObject(parent),
    d_ptr(new HMementoPrivate)
{
}

HMemento::HMemento(HMementoPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HMemento::~HMemento()
{
}

void HMemento::initialize(QVariantMap param)
{
    if (param.contains("dataType"))
        setDataType(param.value("dataType").toStringList());
}

QString HMemento::typeName()
{
    return "HMemento";
}

void HMemento::readContent(QDataStream &s)
{
    quint32 version;
    s >> version;
    s >> d_ptr->types;
    s >> d_ptr->datas;
}

void HMemento::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << d_ptr->types;
    s << d_ptr->datas;
}

void HMemento::setDataType(QStringList value)
{
    if (d_ptr->types == value)
        return;
    d_ptr->types = value;
}

QStringList HMemento::dataType()
{
    return d_ptr->types;
}

void HMemento::save()
{
    d_ptr->datas = d_ptr->testData->select(d_ptr->types);
}

void HMemento::restore()
{
    if (d_ptr->datas.isEmpty())
        return;
    d_ptr->testData->setData(d_ptr->datas);
    d_ptr->model->syncDeviceAll();
}

HE_END_NAMESPACE
