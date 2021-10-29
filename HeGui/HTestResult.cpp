#include "HTestResult_p.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeData/IDataFactory.h"
#include "HeData/ITestData.h"
#include "HeData/ITextStream.h"
#include "HeSql/ISqlHandle.h"
#include "HeSql/ISqlPrint.h"
#include "HeSql/HSql.h"
#include "QXlsx/xlsxdocument.h"
#include <QtCore/QDir>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HTestResultPrivate::HTestResultPrivate()
{
    sqlHandle = HAppContext::getContextPointer<ISqlHandle>("ISqlHandle");
    sqlPrint = HAppContext::getContextPointer<ISqlPrint>("ISqlPrint");
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
    textStream = HAppContext::getContextPointer<IDataFactory>("IDataFactory")->createTextStream("HTextStream");
    textStream->setFileFilter("Excel files (*.xls)");
    xlsxStream = HAppContext::getContextPointer<IDataFactory>("IDataFactory")->createXlsxStream("HXlsxStream");
    xlsxStream->setWriteContent([=](Document *p) { writeContent(p); });
}

void HTestResultPrivate::writeContent(Document *p)
{
    int i, j;
    auto title = QStringList() << "Index" << HCore::toCaptionUnit(exportTypes);
    for (i = 0; i < title.size(); i++)
        p->write(1, i + 1, title.at(i));
    for (i = 0; i < results.size(); i++)
    {
        auto data = QStringList() << QString::number(i + 1) << results.at(i)->toString(exportTypes);
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
    d_ptr->exportFileName.clear();
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

void HTestResult::setExportTypes(QStringList value)
{
    d_ptr->exportTypes = value;
}

void HTestResult::setExportPathName(const QString &value)
{
    d_ptr->exportPathName = value;
}

void HTestResult::setSyncFileName(const QString &value)
{
    d_ptr->syncFileName = value;
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

void HTestResult::exportExcel(int index, int count)
{
    if (isEmpty() || count < 1 || index < 0)
        return;

    QStringList list;
    count = qMin(size() - index, count);
    list << "Index\t" + HCore::toCaptionUnit(d_ptr->exportTypes).join("\t");
    for (int i = 0; i < count; i++)
        list << QString("%1\t").arg(index + i) + d_ptr->results.at(i)->toString(d_ptr->exportTypes).join("\t");
    d_ptr->textStream->setContent(list.join("\n"));
    d_ptr->textStream->saveAsFile("", "");
}

void HTestResult::exportExcelLast()
{
    if (isEmpty())
        return;

    QString text;
    QStringList list;
    text += HCore::toCaptionUnit(d_ptr->exportTypes).join("\t") + "\n";
    text += d_ptr->results.last()->toString(d_ptr->exportTypes).join("\t") + "\n";
    text += HCore::toCaptionUnit("[光谱波长]") + "\t" + HCore::toCaptionUnit("[光谱能量百分比]") + "\n";
    auto poly = d_ptr->results.last()->data("[光谱能量曲线]").value<QPolygonF>();
    for (int i = 0; i < poly.size(); i += 10)
        list << HCore::toString("[光谱波长]", poly[i].x()) + "\t" +  HCore::toString("[光谱能量百分比]", poly[i].y());
    text += list.join("\n");
    d_ptr->textStream->setContent(text);
    d_ptr->textStream->saveAsFile("", "");
}

void HTestResult::exportExcelAppend()
{
    if (isEmpty())
        return;
    QString text;
    if (d_ptr->exportFileName.isEmpty())
    {
        auto path = d_ptr->exportPathName.isEmpty() ? "AutoSave" : d_ptr->exportPathName;
        QDir dir(path);
        if (!dir.exists())
            dir.mkpath(path);
        d_ptr->exportFileName = dir.path() + dir.separator() + QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + ".xls";
        text += "Index\t" + HCore::toCaptionUnit(d_ptr->exportTypes).join("\t") + "\n";
    }
    text += QString("%1\t").arg(d_ptr->index) + d_ptr->results.last()->toString(d_ptr->exportTypes).join("\t") + "\n";
    d_ptr->textStream->setContent(text);
    d_ptr->textStream->appendFile(d_ptr->exportFileName);
    d_ptr->index++;
}

void HTestResult::syncFile()
{
    if (d_ptr->syncFileName.isEmpty() || !d_ptr->modified)
        return;
    if (d_ptr->xlsxStream->writeFile(d_ptr->syncFileName))
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
