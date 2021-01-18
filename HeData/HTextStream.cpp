#include "HTextStream_p.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>

HE_DATA_BEGIN_NAMESPACE

HTextStreamPrivate::HTextStreamPrivate()
{
    fileFilter = "Text files (*.txt)";
}

HTextStream::HTextStream(QObject *parent) :
    ITextStream(*new HTextStreamPrivate, parent)
{
}

HTextStream::HTextStream(HTextStreamPrivate &p, QObject *parent) :
    ITextStream(p, parent)
{
}

HTextStream::~HTextStream()
{
}

QString HTextStream::typeName()
{
    return "HTextStream";
}

QString HTextStream::content()
{
    Q_D(HTextStream);
    return d->content;
}

void HTextStream::setContent(QString value)
{
    Q_D(HTextStream);
    d->content = value;
}

void HTextStream::setReadContent(std::function<void (QTextStream &)> func)
{
    Q_D(HTextStream);
    d->readContent = func;
}

void HTextStream::setWriteContent(std::function<void (QTextStream &)> func)
{
    Q_D(HTextStream);
    d->writeContent = func;
}

bool HTextStream::readFile(QString fileName)
{
    if (fileName.isEmpty())
        return false;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream s(&file);
    auto r = readContent(s);
    file.close();
    return r;
}

bool HTextStream::writeFile(QString fileName)
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

bool HTextStream::readContent(QTextStream &s)
{
    Q_D(HTextStream);
    if (d->readContent != nullptr)
    {
        d->readContent(s);
        return true;
    }
    d->content = s.readAll();
    return true;
}

bool HTextStream::writeContent(QTextStream &s)
{
    Q_D(HTextStream);
    if (d->writeContent != nullptr)
    {
        d->writeContent(s);
        return true;
    }
    if (!d->content.isEmpty())
    {
        s << d->content;
        return true;
    }
    return false;
}

HE_DATA_END_NAMESPACE
