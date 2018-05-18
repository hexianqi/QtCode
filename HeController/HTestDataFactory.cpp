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

void HTestDataFactory::initialize(QVariantMap param)
{
    Q_UNUSED(param)
}

ITestData *HTestDataFactory::createTestData(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    ITestData *test = new HTestData;
    test->initialize(param);
    return test;
}

ITestSpec *HTestDataFactory::createTestSpec(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    ITestSpec *test = new HTestSpec;
    test->initialize(param);
    return test;
}

HE_CONTROLLER_END_NAMESPACE
