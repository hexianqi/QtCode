#include "HSqlFactory_p.h"
#include "HSqliteDatabase.h"
#include "HSqlTableModel.h"
#include "HSqlHandle.h"
#include "HSqlOutput.h"
#include "HSqlBrowser.h"

HE_BEGIN_NAMESPACE

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

HSqlFactory::~HSqlFactory() = default;

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
    auto p = new HSqliteDatabase(this);
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

HE_END_NAMESPACE
