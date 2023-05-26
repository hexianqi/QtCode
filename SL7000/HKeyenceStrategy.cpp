#include "HKeyenceStrategy_p.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"
#include <QtCore/QPoint>
#include <QtCore/QVector>

HKeyenceStrategyPrivate::HKeyenceStrategyPrivate()
{
    actionSupport << ACT_SET_MOTOR_LOCATION
                  << ACT_RESET_MOTOR_LOCATION
                  << ACT_SET_MOTOR_PREPARE_TEST
                  << ACT_SET_MOTOR_CANCEL_TEST
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
    QVariant sample;
    QPoint point;

    switch(action)
    {
    case ACT_SET_MOTOR_LOCATION:
        point = d->testData->data("[电机定位]").toPoint();
        return d->protocol->setData(action, QVariantList() << point.x() << point.y());
    case ACT_RESET_MOTOR_LOCATION:
    case ACT_SET_MOTOR_PREPARE_TEST:
    case ACT_SET_MOTOR_CANCEL_TEST:
        return d->protocol->setData(action);
    case ACT_QUERY_MOTOR_STATE:
        d->protocol->getData(action, sample, QVariant::Int);
        d->testData->setData("[电机状态]", sample);
        return true;
    }
    return false;
}


