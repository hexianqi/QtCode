#include "HSqlFactory_p.h"
#include "HSqlDatabase.h"
#include "HSqlTableModel.h"
#include "HSqlHandle.h"
#include "HSqlBrowser.h"
#include "HProductInfo.h"
#include "HSpecSqlPrint.h"
#include "HeCore/HObjectFactory.h"
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
    qDebug() << __func__;
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
    ISqlDatabase *p = new HSqlDatabase(this);
    p->initialize(param);
    return p;
}

ISqlTableModel *HSqlFactory::createTableModel(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    ISqlTableModel *p = new HSqlTableModel(this);
    p->initialize(param);
    return p;
}

ISqlHandle *HSqlFactory::createHandle(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    ISqlHandle *p = new HSqlHandle(this);
    p->initialize(param);
    return p;
}

ISqlPrint *HSqlFactory::createPrint(QString type, QVariantMap param)
{
    return HObjectFactory::createObject<ISqlPrint>(type, param, this);
}

ISqlBrowser *HSqlFactory::createBrowser(QString type, QWidget *parent, QVariantMap param)
{
    Q_UNUSED(type)
    ISqlBrowser *p = new HSqlBrowser(parent);
    p->initialize(param);
    return p;
}

IProductInfo *HSqlFactory::createProductInfo(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    IProductInfo *p = new HProductInfo(this);
    p->initialize(param);
    return p;
}

void HSqlFactory::registerClass()
{
    HObjectFactory::registerClass<HSpecSqlPrint>("HSpecSqlPrint");
}

HE_SQL_END_NAMESPACE
