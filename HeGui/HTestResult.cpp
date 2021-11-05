#include "HTestResult_p.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeData/IDataFactory.h"
#include "HeData/ITestData.h"
#include "HeSql/ISqlHandle.h"
#include "HeSql/HSql.h"
#include "QXlsx/xlsxdocument.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HTestResultPrivate::HTestResultPrivate()
{
    sqlHandle = HAppContext::getContextPointer<ISqlHandle>("ISqlHandle");
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
    xlsxStream = HAppContext::getContextPointer<IDataFactory>("IDataFactory")->createXlsxStream("HXlsxStream");
    xlsxStream->setWriteContent([=](Document *p) { writeContent(p); });
}

void HTestResultPrivate::writeContent(Document *p)
{
    int i, j;
    auto title = QStringList() << "Index" << HCore::toCaptionUnit(syncType);
    for (i = 0; i < title.size(); i++)
        p->write(1, i + 1, title.at(i));
    for (i = 0; i < results.size(); i++)
    {
        auto data = QStringList() << QString::number(i + 1) << results.at(i)->toString(syncType);
        for (j = 0; j < data.size(); j++)
            p->write(i + 2, j + 1, data.at(j));
    }
}

HTestResult::HTestResult(QObject *parent) :
    QObject(parent),
    d_ptr(new HTestResultPrivate)
{
}

HTestResult::HTestResult(HTestResultPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HTestResult::~HTestResult()
{
    qDebug() << __func__;
}

void HTestResult::initialize(QVariantMap /*param*/)
{
}

QString HTestResult::typeName()
{
    return "HTestResult";
}

ITestData *HTestResult::at(int i)
{
    if (i < 0 || i >= d_ptr->results.size())
        return nullptr;
    return d_ptr->results.at(i);
}

ITestData *HTestResult::last()
{
    if (d_ptr->results.isEmpty())
        return nullptr;
    return d_ptr->results.last();
}

bool HTestResult::isEmpty()
{
    return d_ptr->results.isEmpty();
}

int HTestResult::size()
{
    return d_ptr->results.size();
}

void HTestResult::clear()
{
    if (isEmpty())
        return;
    qDeleteAll(d_ptr->results);
    d_ptr->results.clear();
    d_ptr->index = 1;
    d_ptr->modified = true;
}

void HTestResult::save(bool append)
{
    if (append || isEmpty())
    {
        d_ptr->testData->handleOperation("<编号自增>");
        d_ptr->results.append(d_ptr->testData->clone());
    }
    else
        d_ptr->results.last()->setData(d_ptr->testData->cloneData());
    d_ptr->modified = true;
}

void HTestResult::remove(int index, int count)
{
    if (isEmpty() || count < 1 || index < 0)
        return;
    count = qMin(size() - index, count);
    for (int i = 0; i < count; i++)
    {
        auto data = d_ptr->results.takeAt(index);
        delete data;
    }
}

void HTestResult::setModified(bool b)
{
    d_ptr->modified = b;
}

void HTestResult::setSyncType(QStringList value)
{
    d_ptr->syncType = value;
}

void HTestResult::setSyncFile(const QString &value)
{
    d_ptr->syncFile = value;
    d_ptr->modified = true;
}

void HTestResult::exportDatabase(int index, int count)
{
    if (isEmpty() || count < 1 || index < 0)
        return;
    count = qMin(size() - index, count);
    for (int i = 0; i < count; i++)
        d_ptr->sqlHandle->addRecord(toRecord(index + i), false);
}

void HTestResult::exportDatabaseLast()
{
    if (isEmpty())
        return;
    d_ptr->sqlHandle->addRecord(toRecord(size() - 1));
}

void HTestResult::exportDatabaseAll()
{
    exportDatabase(0, size());
}

void HTestResult::syncFile()
{
    if (d_ptr->syncFile.isEmpty() || !d_ptr->modified)
        return;
    if (d_ptr->xlsxStream->writeFile(d_ptr->syncFile))
        d_ptr->modified = false;
}

QVariantMap HTestResult::toRecord(int index)
{
    QVariantMap record;
    auto data = d_ptr->results.at(index);
    for (const auto &f : d_ptr->sqlHandle->field())
        record.insert(f, data->data(HSql::toType(f)));
    return record;
}

HE_GUI_END_NAMESPACE
