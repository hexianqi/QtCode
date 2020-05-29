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

HErrorType HLuminousStrategy::handle(HActionType action)
{
    Q_D(HLuminousStrategy);
    HErrorType error;
    int sample;

    switch(action)
    {
    case ACT_SET_LUMINOUS_TYPE:
        return d->protocol->setData(action, d->testData->data("[光通道]").toInt());
    case ACT_SET_LUMINOUS_GEARS:
        return d->protocol->setData(action, d->testData->data("[光档位]").toInt() + 1);
    case ACT_GET_LUMINOUS_DATA:
        error = d->protocol->getData(action, sample);
        if (error == E_OK)
            d->testData->setData("[光采样值]", sample);
        return error;
    }
    return E_OK;
}

HE_CONTROLLER_END_NAMESPACE
