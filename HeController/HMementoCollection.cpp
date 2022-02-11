#include "HMementoCollection_p.h"
#include "IControllerFactory.h"
#include "IMemento.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/IDataStream.h"
#include "HeData/HStreamHelper.h"

HE_BEGIN_NAMESPACE

HMementoCollectionPrivate::HMementoCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IControllerFactory>("IControllerFactory");
    dataStream = HAppContext::getContextPointer<IDataFactory>("IDataFactory")->createDataStream("HDataStream");
    dataStream->setMagicNumber(0x01010001);
    dataStream->setFileVersion(0x01010101);
    dataStream->setFileFilter("memento files (*.tmp)");
    dataStream->setReadContent([=](QDataStream &s) { readContent(s); });
    dataStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
}

void HMementoCollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;
    s >> version;
    HStreamHelper::read<QString, IMemento>(s, items, [=](QString type) { return factory->createMemento(type); });
}

void HMementoCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HStreamHelper::write<QString, IMemento>(s, items);
}

HMementoCollection::HMementoCollection() :
    IMementoCollection(*new HMementoCollectionPrivate)
{
}

HMementoCollection::HMementoCollection(HMementoCollectionPrivate &p) :
    IMementoCollection(p)
{
}

HMementoCollection::~HMementoCollection()
{
}

void HMementoCollection::initialize(QVariantMap param)
{
    Q_D(HMementoCollection);
    if (param.contains("fileName"))
        d->fileName = param.value("fileName").toString();
}

QString HMementoCollection::typeName()
{
    return "HMementoCollection";
}

bool HMementoCollection::readFile(QString fileName)
{
    Q_D(HMementoCollection);
    d->fileName = fileName;
    return d->dataStream->readFile(fileName);
}

bool HMementoCollection::writeFile(QString fileName)
{
    Q_D(HMementoCollection);
    if (!fileName.isEmpty())
        d->fileName = fileName;
    return d->dataStream->writeFile(d->fileName);
}

HE_END_NAMESPACE
