#include "HAdjustCollection_p.h"
#include "IDataFactory.h"
#include "IDataStream.h"
#include "IMultStream.h"
#include "IAdjust.h"
#include "HStreamHelper.h"
#include "QXlsx/xlsxdocument.h"
#include "HeCore/HAppContext.h"

HE_BEGIN_NAMESPACE

HAdjustCollectionPrivate::HAdjustCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    dataStream = factory->createDataStream("HDataStream");
    dataStream->setMagicNumber(0x00040001);
    dataStream->setFileVersion(0x01010101);
    dataStream->setFileFilter("Adjust files (*.hca)");
    dataStream->setReadContent([=](QDataStream &s) { readContent(s); });
    dataStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
    multStream = factory->createMultStream("HMultStream");
    multStream->addStream("hca", dataStream);
//    auto xlsxStream = factory->createXlsxStream("HXlsxStream");
//    xlsxStream->setReadContent([=](Document *p) { readContent(p); });
//    xlsxStream->setWriteContent([=](Document *p) { writeContent(p); });
//    multStream->addStream("xlsx", xlsxStream);
}

void HAdjustCollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;
    s >> version;
    HStreamHelper::read<QString, IAdjust>(s, items, [=](QString type) { return factory->createAdjust(type); });
    s >> useIndex;
}

void HAdjustCollectionPrivate::readContent(Document *p)
{
    items.clear();
    useIndex = p->currentSheet()->sheetName();
    for (auto sheetName : p->sheetNames())
    {
        auto sheet = static_cast<Worksheet *>(p->sheet(sheetName));
        if (sheet == nullptr)
            continue;
        auto item = factory->createAdjust("HAdjust");
        item->readContent(sheet);
        items.insert(sheetName, item);
    }
}

void HAdjustCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HStreamHelper::write<QString, IAdjust>(s, items);
    s << useIndex;
}

void HAdjustCollectionPrivate::writeContent(Document *p)
{
    for (auto i = items.begin(); i != items.end(); i++)
    {
        p->addSheet(i.key());
        i.value()->writeContent(p->currentWorksheet());
    }
    p->selectSheet(useIndex);
}

HAdjustCollection::HAdjustCollection() :
    IAdjustCollection(*new HAdjustCollectionPrivate)
{
}

HAdjustCollection::HAdjustCollection(HAdjustCollectionPrivate &p) :
    IAdjustCollection(p)
{
}

HAdjustCollection::~HAdjustCollection()
{
}

QString HAdjustCollection::typeName()
{
    return "HAdjustCollection";
}

QVariantMap HAdjustCollection::correct(QVariantMap value)
{
    auto i = useItem();
    return i == nullptr ? QVariantMap() : i->correct(value);
}

HE_END_NAMESPACE
