#include "HAbstractActionStrategy_p.h"

HE_CONTROLLER_BEGIN_NAMESPACE

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

bool HAbstractActionStrategy::isSupport(HActionType action)
{
    return d_ptr->actionSupport.contains(action);
}

HE_CONTROLLER_END_NAMESPACE
