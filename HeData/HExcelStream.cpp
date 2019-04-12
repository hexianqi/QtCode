#include "HExcelStream_p.h"
#include <QFileDialog>
#include <QTextStream>

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

HExcelStream::HExcelStream(HExcelStreamPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HExcelStream::~HExcelStream()
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
    d_ptr->writeContent = func;
}

bool HExcelStream::saveAsFile(QString caption, QString dir, QString *selectedFileName)
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(nullptr, caption, dir, d_ptr->fileFilter);
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
    if (!writeContent(s))
        return false;
    file.close();
    return true;
}

bool HExcelStream::writeContent(QTextStream &s)
{
    if (d_ptr->writeContent == nullptr)
        return false;
    d_ptr->writeContent(s);
    return true;
}

HE_DATA_END_NAMESPACE

