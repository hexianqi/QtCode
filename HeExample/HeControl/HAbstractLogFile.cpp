#include "HAbstractLogFile_p.h"
#include <QtCore/QDateTime>
#include <QtCore/QDir>
#include <QtWidgets/QApplication>

HE_BEGIN_NAMESPACE

HAbstractLogFilePrivate::HAbstractLogFilePrivate()
{
    path = QApplication::applicationDirPath() + QDir::separator() + "Log";
    name = QApplication::applicationName();
    format = "yyMMdd";
}

HAbstractLogFile::HAbstractLogFile(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractLogFilePrivate)
{
}

HAbstractLogFile::HAbstractLogFile(HAbstractLogFilePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractLogFile::~HAbstractLogFile() = default;

void HAbstractLogFile::setPath(const QString &value)
{
    if (d_ptr->path == value)
        return;
    d_ptr->path = value;
}

void HAbstractLogFile::setName(const QString &value)
{
    if (d_ptr->name == value)
        return;
    d_ptr->name = value;
}

void HAbstractLogFile::setDataTimeFormat(const QString &value)
{
    if (d_ptr->format == value)
        return;
    d_ptr->format = value;
}

QString HAbstractLogFile::fileName(QString format)
{
    QDir dir(d_ptr->path);
    if (!dir.exists())
        dir.mkdir(d_ptr->path);
    if (format.isEmpty())
        format = d_ptr->format;
    return QString("%1%2%3_%4.log").arg(d_ptr->path, QDir::separator(), d_ptr->name, QDateTime::currentDateTime().toString(format));
}

HE_END_NAMESPACE
