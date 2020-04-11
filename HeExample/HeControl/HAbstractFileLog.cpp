#include "HAbstractFileLog_p.h"
#include <QtCore/QDate>
#include <QtCore/QDir>
#include <QtWidgets/QApplication>

HE_CONTROL_BEGIN_NAMESPACE

HAbstractFileLogPrivate::HAbstractFileLogPrivate()
{
    path = qApp->applicationDirPath() + QDir::separator() + "Log";
    dataFormat = "hhhhMMdd";
}

HAbstractFileLog::HAbstractFileLog(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractFileLogPrivate)
{
}

HAbstractFileLog::HAbstractFileLog(HAbstractFileLogPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractFileLog::~HAbstractFileLog()
{
}

void HAbstractFileLog::setPath(QString value)
{
    if (d_ptr->path == value)
        return;
    d_ptr->path = value;
}

void HAbstractFileLog::setName(QString value)
{
    if (d_ptr->name == value)
        return;
    d_ptr->name = value;
}

void HAbstractFileLog::setDataFormat(QString value)
{
    if (d_ptr->dataFormat == value)
        return;
    d_ptr->dataFormat = value;
}

QString HAbstractFileLog::fileName()
{
    return QString("%1%2%3_%4.log").arg(d_ptr->path, QDir::separator(), d_ptr->name, QDate::currentDate().toString(d_ptr->dataFormat));
}

HE_CONTROL_END_NAMESPACE
