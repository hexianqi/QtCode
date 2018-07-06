#include "HAbstractFileStream_p.h"
#include <QFileDialog>

HE_DATA_BEGIN_NAMESPACE

HAbstractFileStreamPrivate::HAbstractFileStreamPrivate(IDataFactory *f)
{
    factory = f;
    magicNumber = 0x00000000;
    fileVersion = 0x01010101;
    fileFilter = QObject::tr("All files (*.*)");
}

HAbstractFileStream::HAbstractFileStream(IDataFactory *f)
    : d_ptr(new HAbstractFileStreamPrivate(f))
{
}

HAbstractFileStream::HAbstractFileStream(HAbstractFileStreamPrivate &p)
    : d_ptr(&p)
{
}

HAbstractFileStream::~HAbstractFileStream()
{
}

void HAbstractFileStream::setFileVersion(quint32 value)
{
    d_ptr->fileFilter = value;
}

void HAbstractFileStream::setFileFilter(QString value)
{
    d_ptr->fileFilter = value;
}

quint32 HAbstractFileStream::fileVersion()
{
    return d_ptr->fileVersion;
}

QString HAbstractFileStream::fileFilter()
{
    return d_ptr->fileFilter;
}

bool HAbstractFileStream::openFile(QString caption, QString dir, QString *selectedFileName)
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(0, caption, dir, d_ptr->fileFilter);
    if (fileName.isEmpty())
        return false;
    if (!readFile(fileName))
        return false;
    if (selectedFileName)
        *selectedFileName = fileName;
    return true;
}

bool HAbstractFileStream::saveAsFile(QString caption, QString dir, QString *selectedFileName)
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(0, caption, dir, d_ptr->fileFilter);
    if (fileName.isEmpty())
        return false;
    if (!writeFile(fileName))
        return false;
    if (selectedFileName)
        *selectedFileName = fileName;
    return true;
}

bool HAbstractFileStream::readFile(QString fileName)
{
    if (fileName.isEmpty())
        return false;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    quint32 magic;
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_10);
    in >> magic;
    if (magic != d_ptr->magicNumber)
        return false;
    in >> d_ptr->fileFilter;
    in >> d_ptr->fileVersion;
    readContent(in);
    file.close();
    return true;
}

bool HAbstractFileStream::writeFile(QString fileName)
{
    if (fileName.isEmpty())
        return false;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return false;
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_10);
    out << d_ptr->magicNumber;
    out << d_ptr->fileFilter;
    out << d_ptr->fileVersion;
    writeContent(out);
    file.close();
    return true;
}

HE_DATA_END_NAMESPACE
