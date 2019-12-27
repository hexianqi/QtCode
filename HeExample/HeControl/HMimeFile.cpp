#include "HMimeFile_p.h"
#include <QtCore/QFile>

HE_CONTROL_BEGIN_NAMESPACE

HMimeFilePrivate::HMimeFilePrivate()
{
    contentType = "application/octet-stream";
    contentEncoding = HMimePart::Base64;
}

HMimeFile::HMimeFile(QString fileName, QObject *parent) :
    HMimePart(*new HMimeFilePrivate, parent)
{
    setFileName(fileName);
}

HMimeFile::HMimeFile(HMimeFilePrivate &p, QString fileName, QObject *parent) :
    HMimePart(p, parent)
{
    setFileName(fileName);
}

HMimeFile::~HMimeFile()
{
}

QString HMimeFile::fileName() const
{
    Q_D(const HMimeFile);
    return d->fileName;
}

void HMimeFile::setFileName(const QString &value)
{
    Q_D(HMimeFile);
    if (d->fileName == value)
        return;
    d->fileName = value;

    QFile file(value, this);
    if (file.open(QIODevice::ReadOnly))
    {
        d->contentName = file.fileName();
        d->content = file.readAll();
        file.close();
    }
}

HE_CONTROL_END_NAMESPACE
