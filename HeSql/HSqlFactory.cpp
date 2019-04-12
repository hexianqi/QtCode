#include "HSqlFactory_p.h"
#include <QDebug>

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

void HSqlFactory::registerClass()
{
//    HFactory::registerClass<HSerialPort>("HSerialPort");
//    HFactory::registerClass<HUsbPortCy>("HUsbPortCy");
//    HFactory::registerClass<HDeviceSL>("HDeviceSL");
}

HE_SQL_END_NAMESPACE
