#include "HDataStream_p.h"
#include <QtCore/QFile>
#include <QtCore/QDataStream>

HE_DATA_BEGIN_NAMESPACE

HDataStreamPrivate::HDataStreamPrivate()
{
    magicNumber = 0x00000000;
    fileVersion = 0x01010101;
    fileFilter = "All files (*.*)";
}

HDataStream::HDataStream(QObject *parent) :
    IDataStream(*new HDataStreamPrivate, parent)
{
}

HDataStream::HDataStream(HDataStreamPrivate &p, QObject *parent) :
    IDataStream(p, parent)
{
}

HDataStream::~HDataStream()
{
}

void HDataStream::initialize(QVariantMap param)
{
    IDataStream::initialize(param);
    if (param.contains("magicNumber"))
        setMagicNumber(param.value("magicNumber").toUInt());
    if (param.contains("fileVersion"))
        setFileVersion(param.value("fileVersion").toUInt());
}

QString HDataStream::typeName()
{
    return "HDataStream";
}

void HDataStream::setMagicNumber(quint32 value)
{
    Q_D(HDataStream);
    d->magicNumber = value;
}

void HDataStream::setFileVersion(quint32 value)
{
    Q_D(HDataStream);
    d->fileVersion = value;
}

void HDataStream::setReadContent(std::function<void (QDataStream &)> func)
{
    Q_D(HDataStream);
    d->readContent = func;
}

void HDataStream::setWriteContent(std::function<void (QDataStream &)> func)
{
    Q_D(HDataStream);
    d->writeContent = func;
}

bool HDataStream::readFile(QString fileName)
{
    Q_D(HDataStream);
    if (fileName.isEmpty())
        return false;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    quint32 magic;
    QDataStream s(&file);
    s.setVersion(QDataStream::Qt_5_10);
    s >> magic;
    if (magic != d->magicNumber)
        return false;
    s >> d->fileFilter;
    s >> d->fileVersion;
    auto r = readContent(s);
    file.close();
    return r;
}

bool HDataStream::writeFile(QString fileName)
{
    Q_D(HDataStream);
    if (fileName.isEmpty())
        return false;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QDataStream s(&file);
    s.setVersion(QDataStream::Qt_5_10);
    s << d->magicNumber;
    s << d->fileFilter;
    s << d->fileVersion;
    auto r = writeContent(s);
    file.close();
    return r;
}

bool HDataStream::readContent(QDataStream &s)
{
    Q_D(HDataStream);
    if (d->readContent == nullptr)
        return false;
    d->readContent(s);
    return true;
}

bool HDataStream::writeContent(QDataStream &s)
{
    Q_D(HDataStream);
    if (d->writeContent == nullptr)
        return false;
    d->writeContent(s);
    return true;
}

HE_DATA_END_NAMESPACE
