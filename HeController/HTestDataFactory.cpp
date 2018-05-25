#include "HTestDataFactory_p.h"
#include "HTestSpec.h"

HE_CONTROLLER_BEGIN_NAMESPACE

HTestDataFactory::HTestDataFactory()
    : d_ptr(new HTestDataFactoryPrivate)
{
}

HTestDataFactory::HTestDataFactory(HTestDataFactoryPrivate &p)
    : d_ptr(&p)
{
}

void HTestDataFactory::initialize(QVariantMap /*param*/)
{
}

QString HTestDataFactory::typeName()
{
    return "HTestDataFactory";
}

ITestData *HTestDataFactory::createTestData(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    ITestData *p = new HTestData;
    p->initialize(param);
    return p;
}

ITestSpec *HTestDataFactory::createTestSpec(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    ITestSpec *p = new HTestSpec;
    p->initialize(param);
    return p;
}

HE_CONTROLLER_END_NAMESPACE
