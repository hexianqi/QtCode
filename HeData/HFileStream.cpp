#include "HFileStream_p.h"
#include <QtWidgets/QFileDialog>

HE_DATA_BEGIN_NAMESPACE

HFileStreamPrivate::HFileStreamPrivate()
{
    magicNumber = 0x00000000;
    fileVersion = 0x01010101;
    fileFilter = "All files (*.*)";
}

HFileStream::HFileStream(QObject *parent) :
    QObject(parent),
    d_ptr(new HFileStreamPrivate)
{
}

HFileStream::~HFileStream() = default;

HFileStream::HFileStream(HFileStreamPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

void HFileStream::initialize(QVariantMap param)
{
    if (param.contains("magicNumber"))
        setMagicNumber(param.value("magicNumber").toUInt());
    if (param.contains("fileVersion"))
        setFileVersion(param.value("fileVersion").toUInt());
    if (param.contains("fileFilter"))
        setFileFilter(param.value("fileFilter").toString());
}

QString HFileStream::typeName()
{
    return "HFileStream";
}

void HFileStream::setMagicNumber(quint32 value)
{
    d_ptr->magicNumber = value;
}

void HFileStream::setFileVersion(quint32 value)
{
    d_ptr->fileVersion = value;
}

void HFileStream::setFileFilter(QString value)
{
    d_ptr->fileFilter = value;
}

void HFileStream::setReadContent(std::function<void(QDataStream &)> func)
{
    d_ptr->readContent = func;
}

void HFileStream::setWriteContent(std::function<void(QDataStream &)> func)
{
    d_ptr->writeContent = func;
}

quint32 HFileStream::fileVersion()
{
    return d_ptr->fileVersion;
}

QString HFileStream::fileFilter()
{
    return d_ptr->fileFilter;
}

bool HFileStream::openFile(QString caption, QString dir, QString *selectedFileName)
{
    auto fileName = QFileDialog::getOpenFileName(nullptr, caption, dir, d_ptr->fileFilter);
    if (fileName.isEmpty())
        return false;
    if (!readFile(fileName))
        return false;
    if (selectedFileName)
        *selectedFileName = fileName;
    return true;
}

bool HFileStream::saveAsFile(QString caption, QString dir, QString *selectedFileName)
{
    auto fileName = QFileDialog::getSaveFileName(nullptr, caption, dir, d_ptr->fileFilter);
    if (fileName.isEmpty())
        return false;
    if (!writeFile(fileName))
        return false;
    if (selectedFileName)
        *selectedFileName = fileName;
    return true;
}

bool HFileStream::readFile(QString fileName)
{
    if (fileName.isEmpty())
        return false;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    quint32 magic;
    QDataStream s(&file);
    s.setVersion(QDataStream::Qt_5_10);
    s >> magic;
    if (magic != d_ptr->magicNumber)
        return false;
    s >> d_ptr->fileFilter;
    s >> d_ptr->fileVersion;
    auto r = readContent(s);
    file.close();
    return r;
}

bool HFileStream::writeFile(QString fileName)
{
    if (fileName.isEmpty())
        return false;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QDataStream s(&file);
    s.setVersion(QDataStream::Qt_5_10);
    s << d_ptr->magicNumber;
    s << d_ptr->fileFilter;
    s << d_ptr->fileVersion;
    auto r = writeContent(s);
    file.close();
    return r;
}

bool HFileStream::readContent(QDataStream &s)
{
    if (d_ptr->readContent == nullptr)
        return false;
    d_ptr->readContent(s);
    return true;
}

bool HFileStream::writeContent(QDataStream &s)
{
    if (d_ptr->writeContent == nullptr)
        return false;
    d_ptr->writeContent(s);
    return true;
}

HE_DATA_END_NAMESPACE
