#include "HElecStrategy_p.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"
#include <QtCore/QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

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

HElecStrategy::~HElecStrategy()
{
    qDebug() << __func__;
}

QString HElecStrategy::typeName()
{
    return "HElecStrategy";
}

HErrorType HElecStrategy::handle(HActionType action)
{
    Q_D(HElecStrategy);
    HErrorType error;
    int sample;
    QVector<int> buff;

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
        error = d->protocol->getData(action, buff);
        if (error == E_OK)
        {
            if (buff.length() > 0)
                d->testData->setData("[实测电压_F]", buff.at(0));
            if (buff.length() > 1)
                d->testData->setData("[实测电流_F]", buff.at(1));
            if (buff.length() > 2)
                d->testData->setData("[反向漏流_F]", buff.at(2));
        }
        return error;
    case ACT_GET_MEASURED_VOLTAGE:
        error = d->protocol->getData(action, sample);
        if (error == E_OK)
            d->testData->setData("[实测电压_F]", sample);
        return error;
    case ACT_GET_MEASURED_CURRENT:
        error = d->protocol->getData(action, sample);
        if (error == E_OK)
            d->testData->setData("[实测电流_F]", sample);
        return error;
    case ACT_GET_REVERSE_CURRENT:
        error = d->protocol->getData(action, sample);
        if (error == E_OK)
            d->testData->setData("[反向漏流_F]", sample);
        return error;
    case ACT_RESET_STATE_TRIGGER:
        return d->protocol->setData(action, 0);
    case ACT_QUERY_STATE_TRIGGER:
        error = d->protocol->getData(action, sample);
        if (error == E_OK)
            d->testData->setData("[触发状态]", sample);
        return error;
    }
    return E_OK;
}

HE_CONTROLLER_END_NAMESPACE
