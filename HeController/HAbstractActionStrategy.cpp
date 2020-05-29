#include "HAbstractActionStrategy_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"

HE_CONTROLLER_BEGIN_NAMESPACE

HAbstractActionStrategyPrivate::HAbstractActionStrategyPrivate()
{
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
}

HAbstractActionStrategy::HAbstractActionStrategy(QObject *parent) :
    IActionStrategy(parent),
    d_ptr(new HAbstractActionStrategyPrivate)
{
}

HAbstractActionStrategy::HAbstractActionStrategy(HAbstractActionStrategyPrivate &p, QObject *parent) :
    IActionStrategy(parent),
    d_ptr(&p)
{
}

void HAbstractActionStrategy::initialize(QVariantMap /*param*/)
{
}

void HAbstractActionStrategy::setProtocol(IProtocol *p)
{
    d_ptr->protocol = p;
}

bool HAbstractActionStrategy::isSupport(HActionType action)
{
    return d_ptr->actionSupport.contains(action);
}

HE_CONTROLLER_END_NAMESPACE
