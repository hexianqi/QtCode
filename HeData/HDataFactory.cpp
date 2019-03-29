#include "HDataFactory_p.h"
#include "HFileStream.h"
#include "HConfigManage.h"
#include "HSpecCalibrate.h"
#include "HSpecCalibrateCollection.h"
#include <QDebug>

HE_DATA_BEGIN_NAMESPACE

HDataFactory::HDataFactory(QObject *parent)
    : QObject(parent), d_ptr(new HDataFactoryPrivate)
{
    registerClass();
}

HDataFactory::HDataFactory(HDataFactoryPrivate &p, QObject *parent)
    :  QObject(parent), d_ptr(&p)
{
    registerClass();
}

HDataFactory::~HDataFactory()
{
    qDebug() << __func__;
}

void HDataFactory::initialize(QVariantMap /*param*/)
{
}

QString HDataFactory::typeName()
{
    return "HDataFactory";
}

IFileStream *HDataFactory::createFileStream(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    IFileStream *p = new HFileStream(this);
    p->initialize(param);
    return p;
}

IConfigManage *HDataFactory::createConfigManage(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    IConfigManage *p = new HConfigManage(this);
    p->initialize(param);
    return p;
}

ISpecCalibrate *HDataFactory::createSpecCalibrate(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    ISpecCalibrate *p = new HSpecCalibrate;
    p->initialize(param);
    return p;
}

ISpecCalibrateCollection *HDataFactory::createSpecCalibrateCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    ISpecCalibrateCollection *p = new HSpecCalibrateCollection(this);
    p->initialize(param);
    return p;
}

void HDataFactory::registerClass()
{
//    HFactory::registerClass<HSerialPort>("HSerialPort");
//    HFactory::registerClass<HUsbPortCy>("HUsbPortCy");
//    HFactory::registerClass<HDeviceSL>("HDeviceSL");
}

HE_DATA_END_NAMESPACE
