#include "HControllerFactory_p.h"
#include "HThreadSpec.h"
#include "HThreadCollection.h"
#include "HTestSpec.h"
#include "HeCore/HObjectFactory.h"

HE_CONTROLLER_BEGIN_NAMESPACE

HControllerFactory::HControllerFactory(QObject *parent)
    : QObject(parent), d_ptr(new HControllerFactoryPrivate)
{
    registerClass();
}

HControllerFactory::HControllerFactory(HControllerFactoryPrivate &p, QObject *parent)
    : QObject(parent), d_ptr(&p)
{
    registerClass();
}

HControllerFactory::~HControllerFactory()
{
}

void HControllerFactory::initialize(QVariantMap /*param*/)
{
}

QString HControllerFactory::typeName()
{
    return "HControllerFactory";
}

IThread *HControllerFactory::createThread(QString type, QVariantMap param)
{
    return HObjectFactory::createObject<IThread>(type, param, this);
}

IThreadCollection *HControllerFactory::createThreadCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    IThreadCollection *p = new HThreadCollection;
    p->initialize(param);
    return p;
}

ITestData *HControllerFactory::createTestData(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    ITestData *p = new HTestData;
    p->initialize(param);
    return p;
}

ITestSpec *HControllerFactory::createTestSpec(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    ITestSpec *p = new HTestSpec;
    p->initialize(param);
    return p;
}

void HControllerFactory::registerClass()
{
    HObjectFactory::registerClass<HThreadSpec>("HThreadSpec");
}

HE_CONTROLLER_END_NAMESPACE
