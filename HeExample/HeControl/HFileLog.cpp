#include "HFileLog_p.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>

HE_CONTROL_BEGIN_NAMESPACE

HFileLog::HFileLog(QObject *parent) :
    HAbstractFileLog(*new HFileLogPrivate, parent)
{
}

HFileLog::HFileLog(HFileLogPrivate &p, QObject *parent) :
    HAbstractFileLog(p, parent)
{
}

bool HFileLog::readContent(QStringList &value)
{
    QFile file(fileName());
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    value.clear();
    while (!file.atEnd())
        value << file.readLine();
    file.close();
    return true;
}

bool HFileLog::writeContent(QStringList value)
{
    QFile file(fileName());
    if (!file.open(QFile::ReadWrite | QFile::Text | QFile::Truncate))
        return false;

    QTextStream s(&file);
    for (const auto &v : value)
        s << v << endl;
    file.close();
    return true;
}

bool HFileLog::appendContent(QStringList value)
{
    QFile file(fileName());
    if (!file.open(QFile::ReadWrite | QFile::Text | QFile::Append))
        return false;

    QTextStream s(&file);
    for (const auto &v : value)
        s << v << endl;
    file.close();
    return true;
}

HE_CONTROL_END_NAMESPACE
