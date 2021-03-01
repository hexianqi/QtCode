#include "HTestResult_p.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeData/IDataFactory.h"
#include "HeData/ITestData.h"
#include "HeData/ITextStream.h"
#include "HeSql/ISqlHandle.h"
#include "HeSql/ISqlPrint.h"
#include "HeSql/HSql.h"
#include <QtCore/QDir>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HTestResultPrivate::HTestResultPrivate()
{
    sqlHandle = HAppContext::getContextPointer<ISqlHandle>("ISqlHandle");
    sqlPrint = HAppContext::getContextPointer<ISqlPrint>("ISqlPrint");
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
    stream = HAppContext::getContextPointer<IDataFactory>("IDataFactory")->createTextStream("HTextStream");
    stream->setFileFilter("Excel files (*.xls)");
}

HTestResult::HTestResult(QObject *parent) :
    ITestResult(parent),
    d_ptr(new HTestResultPrivate)
{
}

HTestResult::HTestResult(HTestResultPrivate &p, QObject *parent) :
    ITestResult(parent),
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
    if (i < 0 || i >= size())
        return nullptr;
    return d_ptr->results.at(i);
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
    qDeleteAll(d_ptr->results);
    d_ptr->results.clear();
    d_ptr->fileName.clear();
    d_ptr->index = 1;
}

void HTestResult::save(bool append)
{
    if (append || isEmpty())
        d_ptr->results.append(d_ptr->testData->clone());
    else
        d_ptr->results.last()->setData(d_ptr->testData->cloneData());
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

void HTestResult::setPathName(const QString &value)
{
    d_ptr->pathName = value;
}

void HTestResult::printPreviewLast()
{
    if (isEmpty())
        return;
    d_ptr->sqlHandle->addRecord(toRecord(size() - 1), false);
    d_ptr->sqlPrint->printPreview();
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

void HTestResult::exportExcel(QStringList types, int index, int count)
{
    if (isEmpty() || count < 1 || index < 0)
        return;
    count = qMin(size() - index, count);
    QStringList list;
    for (int i = 0; i < count; i++)
        list << QString("%1\t").arg(index+i) + d_ptr->results.at(i)->toString(types).join("\t");
    list.prepend("Index\t" + HCore::toCaptionUnit(types).join("\t"));
    d_ptr->stream->setContent(list.join("\n"));
    d_ptr->stream->saveAsFile("", "");
}

void HTestResult::exportExcelLast(QStringList types)
{
    if (isEmpty())
        return;
    QString text;
    text += HCore::toCaptionUnit(types).join("\t") + "\n";
    text += d_ptr->results.last()->toString(types).join("\t") + "\n";
    d_ptr->stream->setContent(text);
    d_ptr->stream->saveAsFile("", "");
}

void HTestResult::exportExcelAppend(QStringList types)
{
    if (isEmpty())
        return;
    QString text;
    if (d_ptr->fileName.isEmpty())
    {
        auto path = d_ptr->pathName.isEmpty() ? "AutoSave" : d_ptr->pathName;
        QDir dir(path);
        if (!dir.exists())
            dir.mkpath(path);
        d_ptr->fileName = dir.path() + dir.separator() + QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + ".xls";
        text += "Index\t" + HCore::toCaptionUnit(types).join("\t") + "\n";
    }
    text += QString("%1\t").arg(d_ptr->index) + d_ptr->results.last()->toString(types).join("\t") + "\n";
    d_ptr->stream->setContent(text);
    d_ptr->stream->appendFile(d_ptr->fileName);
    d_ptr->index++;
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
