#include "HTextExport_p.h"
#include "IDataFactory.h"
#include "ITextStream.h"
#include "ITextExportTemplate.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QDateTime>
#include <QtCore/QDir>

HE_BEGIN_NAMESPACE

HTextExportPrivate::HTextExportPrivate()
{
    stream = HAppContext::getContextPointer<IDataFactory>("IDataFactory")->createTextStream("HTextStream");
    stream->setFileFilter("Excel files (*.xls)");
}

HTextExport::HTextExport(QObject *parent) :
    QObject(parent),
    d_ptr(new HTextExportPrivate)
{
}

HTextExport::HTextExport(HTextExportPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HTextExport::~HTextExport() = default;

void HTextExport::initialize(QVariantMap /*param*/)
{

}

QString HTextExport::typeName()
{
    return "HTextExport";
}

ITextExportTemplate *HTextExport::textTemplate()
{
    return d_ptr->textTemplate;
}

void HTextExport::setTextTemplate(ITextExportTemplate *p)
{
    if (d_ptr->textTemplate == p)
        return;
    d_ptr->textTemplate = p;
}

void HTextExport::setExportPath(const QString &value)
{
    if (d_ptr->pathName == value)
        return;
    d_ptr->pathName = value;
    clear();
}

void HTextExport::setFileName(const QString &value)
{
    if (d_ptr->fileName == value)
        return;
    d_ptr->fileName = value;
}

bool HTextExport::save(QString fileName)
{
    if (!isValid())
        return false;
    if (!fileName.isEmpty())
        d_ptr->fileName = fileName;
    if (d_ptr->fileName.isEmpty())
        d_ptr->fileName = generateFileName();
    auto text = d_ptr->textTemplate->content(true);
    d_ptr->stream->setContent(text);
    return d_ptr->stream->writeFile(d_ptr->fileName);
}

bool HTextExport::saveAs()
{
    if (!isValid())
        return false;
    auto text = d_ptr->textTemplate->content(true);
    d_ptr->stream->setContent(text);
    return d_ptr->stream->saveAsFile("", "");
}

bool HTextExport::append()
{
    if (!isValid())
        return false;

    auto b = false;
    if (d_ptr->fileName.isEmpty())
    {
        d_ptr->fileName = generateFileName();
        b = true;
    }
    auto text = d_ptr->textTemplate->content(b);
    d_ptr->stream->setContent(text);
    return d_ptr->stream->appendFile(d_ptr->fileName);
}

void HTextExport::clear()
{
    d_ptr->fileName.clear();
}

bool HTextExport::isValid()
{
    return d_ptr->textTemplate != nullptr;
}

QString HTextExport::generateFileName()
{
    auto path = d_ptr->pathName.isEmpty() ? "AutoSave" : d_ptr->pathName;
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(path);
    return dir.path() + dir.separator() + QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + ".xls";
}

HE_END_NAMESPACE
