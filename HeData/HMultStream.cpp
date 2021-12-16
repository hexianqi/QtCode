#include "HMultStream_p.h"
#include <QtCore/QFileInfo>

HE_BEGIN_NAMESPACE

IStream *HMultStreamPrivate::findStream(QString fileName)
{
    auto info = QFileInfo(fileName);
    auto suffix = info.suffix();
    for (auto i = streams.begin(); i != streams.end(); i++)
    {
        if (i.key().contains(suffix))
            return i.value();
    }
    return defaultStream;
}

HMultStream::HMultStream(QObject *parent) :
    HAbstractStream(*new HMultStreamPrivate, parent)
{
}

HMultStream::HMultStream(HMultStreamPrivate &p, QObject *parent) :
    HAbstractStream(p, parent)
{
}

HMultStream::~HMultStream()
{
}

QString HMultStream::typeName()
{
    return "HMultStream";
}

QString HMultStream::fileFilter()
{
    Q_D(HMultStream);
    if (d->fileFilter.isEmpty())
    {
        QStringList list;
        for (auto i : d->streams)
            list << i->fileFilter();
        d->fileFilter = list.join(";;");
    }
    return d->fileFilter;
}

bool HMultStream::readFile(QString fileName)
{
    Q_D(HMultStream);
    auto stream = d->findStream(fileName);
    if (stream == nullptr)
        return false;
    return stream->readFile(fileName);
}

bool HMultStream::writeFile(QString fileName)
{
    Q_D(HMultStream);
    auto stream = d->findStream(fileName);
    if (stream == nullptr)
        return false;
    return stream->writeFile(fileName);
}

void HMultStream::addStream(QString suffix, IStream *p, bool focus)
{
    Q_D(HMultStream);
    d->streams.insert(suffix, p);
    if (focus)
        d->defaultStream = p;
    d->fileFilter.clear();
}

HE_END_NAMESPACE
