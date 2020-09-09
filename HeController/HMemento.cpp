#include "HMemento_p.h"
#include "IModel.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/IFileStream.h"
#include "HeData/ITestData.h"
#include <QtCore/QDataStream>

HE_CONTROLLER_BEGIN_NAMESPACE

HMementoPrivate::HMementoPrivate()
{
    model = HAppContext::getContextPointer<IModel>("IModel");
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
    fileStream = HAppContext::getContextPointer<IDataFactory>("IDataFactory")->createFileStream("HFileStream");
    fileStream->setMagicNumber(0x01010001);
    fileStream->setFileVersion(0x01010101);
    fileStream->setFileFilter("memento files (*.tmp)");
    fileStream->setReadContent([=](QDataStream &s) { readContent(s); });
    fileStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
}

void HMementoPrivate::readContent(QDataStream &s)
{
    quint32 version;
    s >> version;
    s >> datas;
}

void HMementoPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << datas;
}

HMemento::HMemento(QObject *parent) :
    IMemento(parent),
    d_ptr(new HMementoPrivate)
{
}

HMemento::HMemento(HMementoPrivate &p, QObject *parent) :
    IMemento(parent),
    d_ptr(&p)
{
}

HMemento::~HMemento()
{
}

void HMemento::initialize(QVariantMap param)
{
    if (param.contains("fileName"))
        d_ptr->fileName = param.value("fileName").toString();
    if (param.contains("itemTypes"))
        setItems(param.value("itemTypes").toStringList());
}

QString HMemento::typeName()
{
    return "HMemento";
}

bool HMemento::readFile(QString fileName)
{
    d_ptr->fileName = fileName;
    return d_ptr->fileStream->readFile(fileName);
}

bool HMemento::writeFile()
{
    return d_ptr->fileStream->writeFile(d_ptr->fileName);
}

void HMemento::setItems(QStringList value)
{
    if (d_ptr->items == value)
        return;
    d_ptr->items = value;
}

void HMemento::save()
{
    d_ptr->datas = d_ptr->testData->select(d_ptr->items);
}

void HMemento::restore()
{
    if (d_ptr->datas.isEmpty())
        return;
    d_ptr->testData->setData(d_ptr->datas);
    d_ptr->model->syncDeviceWhole();
}

HE_CONTROLLER_END_NAMESPACE
