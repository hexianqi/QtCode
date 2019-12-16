#include "HElecStrategy_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestElec.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include <QtCore/QVector>

HE_CONTROLLER_BEGIN_NAMESPACE

HElecStrategyPrivate::HElecStrategyPrivate()
{
    actionSupport << ACT_SET_SOURCE_MODE
                  << ACT_SET_OUTPUT_VOLTAGE
                  << ACT_SET_OUTPUT_CURRENT
                  << ACT_SET_GEARS_OUTPUT_CURRENT
                  << ACT_SET_REVERSE_VOLTAGE
                  << ACT_GET_ELEC_PARAM
                  << ACT_GET_MEASURED_VOLTAGE
                  << ACT_GET_MEASURED_CURRENT
                  << ACT_GET_REVERSE_CURRENT;
    protocol = HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection")->value("Elec");
    testElec = HAppContext::getContextPointer<ITestElec>("ITestElec");
}

HElecStrategy::HElecStrategy(QObject *parent) :
    HAbstractActionStrategy(*new HElecStrategyPrivate, parent)
{
}

HElecStrategy::HElecStrategy(HElecStrategyPrivate &p, QObject *parent) :
    HAbstractActionStrategy(p, parent)
{
}

HElecStrategy::~HElecStrategy()
{
}

QString HElecStrategy::typeName()
{
    return "HElecStrategy";
}

HErrorType HElecStrategy::handle(HActionType action)
{
    Q_D(HElecStrategy);
    HErrorType error;
    int isample;
    QVector<int> ibuff;

    switch(action)
    {
    case ACT_SET_SOURCE_MODE:
        return d->protocol->setData(action, d->testElec->data("[电源模式]").toInt());
    case ACT_SET_OUTPUT_VOLTAGE:
        return d->protocol->setData(action, d->testElec->data("[输出电压_F]").toInt());
    case ACT_SET_OUTPUT_CURRENT:
        return d->protocol->setData(action, d->testElec->data("[输出电流_F]").toInt());
    case ACT_SET_GEARS_OUTPUT_CURRENT:
        return d->protocol->setData(action, d->testElec->data("[输出电流_档位]").toInt());
    case ACT_SET_REVERSE_VOLTAGE:
        return d->protocol->setData(action, d->testElec->data("[反向电压_F]").toInt());
    case ACT_GET_ELEC_PARAM:
        error = d->protocol->getData(action, ibuff);
        if (error == E_OK)
            d->testElec->setSample(ibuff);
        return error;
    case ACT_GET_MEASURED_VOLTAGE:
        error = d->protocol->getData(action, isample);
        if (error == E_OK)
            d->testElec->setParam(MeasuredVoltage, isample);
        return error;
    case ACT_GET_MEASURED_CURRENT:
        error = d->protocol->getData(action, isample);
        if (error == E_OK)
            d->testElec->setParam(MeasuredCurrent, isample);
        return error;
    case ACT_GET_REVERSE_CURRENT:
        error = d->protocol->getData(action, isample);
        if (error == E_OK)
            d->testElec->setParam(ReverseCurrent, isample);
        return error;
    }
    return E_OK;
}

HE_CONTROLLER_END_NAMESPACE
