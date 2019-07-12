#include "HKeepFileLog_p.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>

HE_CONTROL_BEGIN_NAMESPACE

HKeepFileLog::HKeepFileLog(QObject *parent) :
    HAbstractFileLog(*new HKeepFileLogPrivate, parent)
{
    init();
}

HKeepFileLog::HKeepFileLog(HKeepFileLogPrivate &p, QObject *parent) :
    HAbstractFileLog(p, parent)
{
    init();
}

HKeepFileLog::~HKeepFileLog()
{
    Q_D(HKeepFileLog);
    if (d->file->isOpen())
        d->file->close();
}

bool HKeepFileLog::readContent(QStringList &value)
{
    Q_D(HKeepFileLog);
    reopenFileIfNeeded();
    value.clear();
    if (!d->file->reset())
        return false;
    while (!d->file->atEnd())
        value << d->file->readLine();
    return true;
}

bool HKeepFileLog::writeContent(QStringList value)
{
    Q_D(HKeepFileLog);
    reopenFileIfNeeded();
    d->file->resize(0);
    QTextStream s(d->file);
    for (auto v : value)
        s << v << endl;
    return true;
}

bool HKeepFileLog::appendContent(QStringList value)
{
    Q_D(HKeepFileLog);
    reopenFileIfNeeded();
    QTextStream s(d->file);
    for (auto v : value)
        s << v << endl;
    return true;
}

void HKeepFileLog::init()
{
    Q_D(HKeepFileLog);
    d->file = new QFile(this);
    d->fileName = "";
}

void HKeepFileLog::reopenFileIfNeeded()
{
    Q_D(HKeepFileLog);
    auto name = fileName();
    if (name == d->fileName)
        return;
    d->fileName = name;
    if (d->file->isOpen())
        d->file->close();
    d->file->setFileName(name);
    d->file->open(QIODevice::ReadWrite | QIODevice::Append | QFile::Text);
}

HE_CONTROL_END_NAMESPACE
