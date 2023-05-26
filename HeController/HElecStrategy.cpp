#include "HElecStrategy_p.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HElecStrategyPrivate::HElecStrategyPrivate()
{
    actionSupport << ACT_SET_SOURCE_MODE
                  << ACT_SET_OUTPUT_VOLTAGE
                  << ACT_SET_OUTPUT_CURRENT
                  << ACT_SET_GEARS_OUTPUT_CURRENT
                  << ACT_SET_REVERSE_VOLTAGE
                  << ACT_GET_ELEC_DATA
                  << ACT_GET_MEASURED_VOLTAGE
                  << ACT_GET_MEASURED_CURRENT
                  << ACT_GET_REVERSE_CURRENT
                  << ACT_RESET_STATE_TRIGGER
                  << ACT_QUERY_STATE_TRIGGER;
}

HElecStrategy::HElecStrategy(QObject *parent) :
    HAbstractActionStrategy(*new HElecStrategyPrivate, parent)
{
}

HElecStrategy::HElecStrategy(HElecStrategyPrivate &p, QObject *parent) :
    HAbstractActionStrategy(p, parent)
{
}

HElecStrategy::~HElecStrategy() = default;

QString HElecStrategy::typeName()
{
    return "HElecStrategy";
}

bool HElecStrategy::handle(HActionType action)
{
    Q_D(HElecStrategy);
    QVariant sample;
    QVariantList samples;

    switch(action)
    {
    case ACT_SET_SOURCE_MODE:
        return d->protocol->setData(action, d->testData->data("[电源模式]").toInt());
    case ACT_SET_OUTPUT_VOLTAGE:
        return d->protocol->setData(action, d->testData->data("[输出电压_F]").toInt());
    case ACT_SET_OUTPUT_CURRENT:
        return d->protocol->setData(action, d->testData->data("[输出电流_F]").toInt());
    case ACT_SET_GEARS_OUTPUT_CURRENT:
        return d->protocol->setData(action, d->testData->data("[输出电流_档位]").toInt());
    case ACT_SET_REVERSE_VOLTAGE:
        return d->protocol->setData(action, d->testData->data("[反向电压_F]").toInt());
    case ACT_GET_ELEC_DATA:
        d->protocol->getData(action, samples, QVariant::Int);
        if (samples.length() > 0)
            d->testData->setData("[实测电压_F]", samples.at(0));
        if (samples.length() > 1)
            d->testData->setData("[实测电流_F]", samples.at(1));
        if (samples.length() > 2)
            d->testData->setData("[反向漏流_F]", samples.at(2));
        return true;
    case ACT_GET_MEASURED_VOLTAGE:
        d->protocol->getData(action, sample, QVariant::Int);
        d->testData->setData("[实测电压_F]", sample);
        return true;
    case ACT_GET_MEASURED_CURRENT:
        d->protocol->getData(action, sample, QVariant::Int);
        d->testData->setData("[实测电流_F]", sample);
        return true;
    case ACT_GET_REVERSE_CURRENT:
        d->protocol->getData(action, sample, QVariant::Int);
        d->testData->setData("[反向漏流_F]", sample);
        return true;
    case ACT_RESET_STATE_TRIGGER:
        return d->protocol->setData(action, 0);
    case ACT_QUERY_STATE_TRIGGER:
        d->protocol->getData(action, sample, QVariant::Int);
        d->testData->setData("[触发状态]", sample);
        return true;
    }
    return false;
}

HE_END_NAMESPACE
