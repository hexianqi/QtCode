#include "HMotorStrategy_p.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"

HE_BEGIN_NAMESPACE

HMotorStrategyPrivate::HMotorStrategyPrivate()
{
    actionSupport << ACT_SET_MOTOR_LOCATION
                  << ACT_RESET_MOTOR_LOCATION
                  << ACT_QUERY_MOTOR_STATE;
}

HMotorStrategy::HMotorStrategy(QObject *parent) :
    HAbstractActionStrategy(*new HMotorStrategyPrivate, parent)
{
}

HMotorStrategy::HMotorStrategy(HMotorStrategyPrivate &p, QObject *parent) :
    HAbstractActionStrategy(p, parent)
{
}

HMotorStrategy::~HMotorStrategy() = default;

QString HMotorStrategy::typeName()
{
    return "HMotorStrategy";
}

bool HMotorStrategy::handle(HActionType action)
{
    Q_D(HMotorStrategy);
    int sample;

    switch(action)
    {
    case ACT_SET_MOTOR_LOCATION:
        return d->protocol->setData(action, d->testData->data("[电机定位]").toInt());
    case ACT_RESET_MOTOR_LOCATION:
        return d->protocol->setData(action);
    case ACT_QUERY_MOTOR_STATE:
        d->protocol->getData(action, sample);
        d->testData->setData("[电机状态]", sample);
        return true;
    }
    return false;
}

HE_END_NAMESPACE
