#include "HKeyenceStrategy_p.h"
#include "HeData/ITestData.h"

HKeyenceStrategyPrivate::HKeyenceStrategyPrivate()
{
    actionSupport << ACT_SET_MOTOR_LOCATION
                  << ACT_RESET_MOTOR_LOCATION
                  << ACT_RESET_MOTOR_STATE
                  << ACT_QUERY_MOTOR_STATE;
}

HKeyenceStrategy::HKeyenceStrategy(QObject *parent) :
    HAbstractActionStrategy(*new HKeyenceStrategyPrivate, parent)
{
}

HKeyenceStrategy::HKeyenceStrategy(HKeyenceStrategyPrivate &p, QObject *parent) :
    HAbstractActionStrategy(p, parent)
{
}

HKeyenceStrategy::~HKeyenceStrategy() = default;

QString HKeyenceStrategy::typeName()
{
    return "HKeyenceStrategy";
}

bool HKeyenceStrategy::handle(HActionType action)
{
    Q_D(HKeyenceStrategy);
    switch(action)
    {
    case ACT_SET_MOTOR_LOCATION:
        return true;
    case ACT_RESET_MOTOR_LOCATION:
        return true;
    case ACT_RESET_MOTOR_STATE:
        d->testData->setData("[电机状态]", 0);
        return true;
    case ACT_QUERY_MOTOR_STATE:
        d->testData->setData("[电机状态]", 1);
        return true;
    }
    return false;
}


