#include "HDataFactory_p.h"
#include "HFileStream.h"
#include "HConfigManage.h"
#include "HSpecCalibrate.h"
#include "HSpecCalibrateCollection.h"

HE_DATA_BEGIN_NAMESPACE

HDataFactory::HDataFactory(QObject *parent)
    : QObject(parent), d_ptr(new HDataFactoryPrivate)
{
}

HDataFactory::HDataFactory(HDataFactoryPrivate &p, QObject *parent)
    :  QObject(parent), d_ptr(&p)
{
}

HDataFactory::~HDataFactory()
{
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

HE_DATA_END_NAMESPACE
