#include "HLogFile_p.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>

HE_BEGIN_NAMESPACE

HLogFile::HLogFile(QObject *parent) :
    HAbstractLogFile(*new HLogFilePrivate, parent)
{
}

HLogFile::HLogFile(HLogFilePrivate &p, QObject *parent) :
    HAbstractLogFile(p, parent)
{
}

HLogFile::~HLogFile() = default;

QStringList HLogFile::readLines()
{
    QStringList list;
    QFile file(fileName());
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return list;
    while (!file.atEnd())
        list << file.readLine();
    file.close();
    return list;
}

QString HLogFile::readAll()
{
    QFile file(fileName());
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return "";
    QString str = file.readAll();
    file.close();
    return str;
}

bool HLogFile::write(const QStringList &value)
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

bool HLogFile::write(const QString &value)
{
    QFile file(fileName());
    if (!file.open(QFile::ReadWrite | QFile::Text | QFile::Truncate))
        return false;

    QTextStream s(&file);
    s << value << endl;
    file.close();
    return true;
}

bool HLogFile::append(const QStringList &value)
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

bool HLogFile::append(const QString &value)
{
    QFile file(fileName());
    if (!file.open(QFile::ReadWrite | QFile::Text | QFile::Append))
        return false;

    QTextStream s(&file);
    s << value << endl;
    file.close();
    return true;
}

HE_END_NAMESPACE
