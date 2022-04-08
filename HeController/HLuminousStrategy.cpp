#include "HLuminousStrategy_p.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HLuminousStrategyPrivate::HLuminousStrategyPrivate()
{
    actionSupport << ACT_SET_LUMINOUS_TYPE
                  << ACT_SET_LUMINOUS_GEARS
                  << ACT_GET_LUMINOUS_DATA
                  << ACT_START_ANGLE_TEST
                  << ACT_GET_ANGLE_DISTRIBUTION;
}

HLuminousStrategy::HLuminousStrategy(QObject *parent) :
    HAbstractActionStrategy(*new HLuminousStrategyPrivate, parent)
{
}

HLuminousStrategy::HLuminousStrategy(HLuminousStrategyPrivate &p, QObject *parent) :
    HAbstractActionStrategy(p, parent)
{
}

HLuminousStrategy::~HLuminousStrategy() = default;

QString HLuminousStrategy::typeName()
{
    return "HLuminousStrategy";
}

bool HLuminousStrategy::handle(HActionType action)
{
    Q_D(HLuminousStrategy);
    int sample;
    QVector<double> buff;

    switch(action)
    {
    case ACT_SET_LUMINOUS_TYPE:
        return d->protocol->setData(action, d->testData->data("[光通道]").toInt());
    case ACT_SET_LUMINOUS_GEARS:
        return d->protocol->setData(action, d->testData->data("[光档位]").toInt() + 1);
    case ACT_GET_LUMINOUS_DATA:
        d->protocol->getData(action, sample);
        d->testData->setData("[光采样值]", sample);
        return true;
    case ACT_START_ANGLE_TEST:
        return d->protocol->setData(action);
    case ACT_GET_ANGLE_DISTRIBUTION:
        d->protocol->getData(action, buff);
        d->testData->setData("[光强角度分布采样值]", QVariant::fromValue(buff));
        return true;
    }
    return false;
}

HE_END_NAMESPACE
