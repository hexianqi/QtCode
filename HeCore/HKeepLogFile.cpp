#include "HKeepLogFile_p.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>

HE_BEGIN_NAMESPACE

HKeepLogFile::HKeepLogFile(QObject *parent) :
    HAbstractLogFile(*new HKeepLogFilePrivate, parent)
{
    init();
}

HKeepLogFile::HKeepLogFile(HKeepLogFilePrivate &p, QObject *parent) :
    HAbstractLogFile(p, parent)
{
    init();
}

HKeepLogFile::~HKeepLogFile()
{
    Q_D(HKeepLogFile);
    if (d->file->isOpen())
        d->file->close();
}

QStringList HKeepLogFile::readLines()
{
    Q_D(HKeepLogFile);
    QStringList list;
    openFile();
    if (!d->file->reset())
        return list;
    while (!d->file->atEnd())
        list << d->file->readLine();
    return list;
}

QString HKeepLogFile::readAll()
{
    Q_D(HKeepLogFile);
    openFile();
    return d->file->readAll();
}

bool HKeepLogFile::write(const QStringList &value)
{
    Q_D(HKeepLogFile);
    openFile();
    d->file->resize(0);
    QTextStream s(d->file);
    for (const auto &v : value)
        s << v << endl;
    return true;
}

bool HKeepLogFile::write(const QString &value)
{
    Q_D(HKeepLogFile);
    openFile();
    d->file->resize(0);
    QTextStream s(d->file);
    s << value << endl;
    return true;
}

bool HKeepLogFile::append(const QStringList &value)
{
    Q_D(HKeepLogFile);
    openFile();
    QTextStream s(d->file);
    for (const auto &v : value)
        s << v << endl;
    return true;
}

bool HKeepLogFile::append(const QString &value)
{
    Q_D(HKeepLogFile);
    openFile();
    QTextStream s(d->file);
    s << value << endl;
    return true;
}

void HKeepLogFile::clear()
{
    Q_D(HKeepLogFile);
    d->currentRow = 0;
    d->fileName.clear();
    if (d->file->isOpen())
        d->file->close();
}

void HKeepLogFile::setMaxRow(int value)
{
    Q_D(HKeepLogFile);
    if (value < 0 || value == d->maxRow)
        return;
    d->maxRow = value;
    clear();
}

void HKeepLogFile::setMaxSize(int value)
{
    Q_D(HKeepLogFile);
    if (value < 0 || value == d->maxSize)
        return;
    d->maxSize = value;
    clear();
}

void HKeepLogFile::init()
{
    Q_D(HKeepLogFile);
    d->file = new QFile(this);
    d->fileName = "";
}

void HKeepLogFile::openFile()
{
    Q_D(HKeepLogFile);
    auto name = generateFileName();
    if (name == d->fileName)
        return;
    if (d->file->isOpen())
        d->file->close();
    d->fileName = name;
    d->file->setFileName(name);
    d->file->open(QIODevice::ReadWrite | QIODevice::Append | QFile::Text);
}

QString HKeepLogFile::generateFileName()
{
    Q_D(HKeepLogFile);
    if (d->maxRow > 0)
    {
        d->currentRow++;
        if (d->fileName.isEmpty() || d->currentRow >= d->maxRow)
        {
            d->currentRow = 0;
            return fileName("yyMMddHHmmss");
        }
    }
    else if (d->maxSize > 0)
    {
        if (d->fileName.isEmpty() || d->file->size() > d->maxSize * 1024)
            return fileName("yyMMddHHmmss");
    }
    else
    {
        return fileName("yyMMdd");
    }
    return d->fileName;
}

HE_END_NAMESPACE
