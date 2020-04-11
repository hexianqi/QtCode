#include "HExcelStream_p.h"
#include <QtCore/QTextStream>
#include <QtWidgets/QFileDialog>

HE_DATA_BEGIN_NAMESPACE

HExcelStreamPrivate::HExcelStreamPrivate()
{
    fileFilter = "Excel files (*.xls)";
}

HExcelStream::HExcelStream(QObject *parent) :
    QObject(parent),
    d_ptr(new HExcelStreamPrivate)
{
}

HExcelStream::~HExcelStream() = default;

HExcelStream::HExcelStream(HExcelStreamPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

void HExcelStream::initialize(QVariantMap /*param*/)
{

}

QString HExcelStream::typeName()
{
    return "HExcelStream";
}

void HExcelStream::setWriteContent(std::function<void (QTextStream &)> func)
{
    d_ptr->writeContentFunc = func;
}

void HExcelStream::setWriteContent(QString value)
{
    d_ptr->writeContent = value;
}

QString HExcelStream::fileFilter()
{
    return d_ptr->fileFilter;
}

bool HExcelStream::saveAsFile(QString caption, QString dir, QString *selectedFileName)
{
    auto fileName = QFileDialog::getSaveFileName(nullptr, caption, dir, fileFilter());
    if (fileName.isEmpty())
        return false;
    if (!writeFile(fileName))
        return false;
    if (selectedFileName)
        *selectedFileName = fileName;
    return true;
}

bool HExcelStream::writeFile(QString fileName)
{
    if (fileName.isEmpty())
        return false;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream s(&file);
    auto r = writeContent(s);
    file.close();
    return r;
}

bool HExcelStream::writeContent(QTextStream &s)
{
    if (d_ptr->writeContentFunc != nullptr)
    {
        d_ptr->writeContentFunc(s);
        return true;
    }
    if (!d_ptr->writeContent.isEmpty())
    {
        s << d_ptr->writeContent;
        return true;
    }
    return false;
}

HE_DATA_END_NAMESPACE

