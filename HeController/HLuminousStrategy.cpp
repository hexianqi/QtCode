#include "HLuminousStrategy_p.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"
#include <QtCore/QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HLuminousStrategyPrivate::HLuminousStrategyPrivate()
{
    actionSupport << ACT_SET_LUMINOUS_TYPE
                  << ACT_SET_LUMINOUS_GEARS
                  << ACT_GET_LUMINOUS_DATA;
}

HLuminousStrategy::HLuminousStrategy(QObject *parent) :
    HAbstractActionStrategy(*new HLuminousStrategyPrivate, parent)
{
}

HLuminousStrategy::HLuminousStrategy(HLuminousStrategyPrivate &p, QObject *parent) :
    HAbstractActionStrategy(p, parent)
{
}

HLuminousStrategy::~HLuminousStrategy()
{
    qDebug() << __func__;
}

QString HLuminousStrategy::typeName()
{
    return "HLuminousStrategy";
}

bool HLuminousStrategy::handle(HActionType action)
{
    Q_D(HLuminousStrategy);
    int sample;

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
    }
    return false;
}

HE_CONTROLLER_END_NAMESPACE
