#include "HSqlFactory_p.h"
#include "HSqlDatabase.h"
#include "HSqlTableModel.h"
#include "HSqlHandle.h"
#include "HSqlOutput.h"
#include "HSqlBrowser.h"
#include <QtCore/QDebug>

HE_SQL_BEGIN_NAMESPACE

HSqlFactory::HSqlFactory(QObject *parent) :
    QObject(parent),
    d_ptr(new HSqlFactoryPrivate)
{
    registerClass();
}

HSqlFactory::HSqlFactory(HSqlFactoryPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    registerClass();
}

HSqlFactory::~HSqlFactory()
{
    qDebug() << endl << __func__;
}

void HSqlFactory::initialize(QVariantMap /*param*/)
{
}

QString HSqlFactory::typeName()
{
    return "HSqlFactory";
}

ISqlDatabase *HSqlFactory::createDatabase(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HSqlDatabase(this);
    p->initialize(param);
    return p;
}

ISqlTableModel *HSqlFactory::createTableModel(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HSqlTableModel(this);
    p->initialize(param);
    return p;
}

ISqlHandle *HSqlFactory::createHandle(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HSqlHandle(this);
    p->initialize(param);
    return p;
}

ISqlOutput *HSqlFactory::createOutput(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HSqlOutput(this);
    p->initialize(param);
    return p;
}

ISqlBrowser *HSqlFactory::createBrowser(QString type, QWidget *parent, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HSqlBrowser(parent);
    p->initialize(param);
    return p;
}

void HSqlFactory::registerClass()
{
}

HE_SQL_END_NAMESPACE
