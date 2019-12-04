#include "HSpecStrategy_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestSpec.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include <QtCore/QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HSpecStrategyPrivate::HSpecStrategyPrivate()
{
    actionSupport << ACT_SET_INTEGRAL_TIME
                  << ACT_SET_SPECTRUM_AVG_TIMES
                  << ACT_SET_SPECTRUM_SAMPLE_DELAY
                  << ACT_SET_RAM
                  << ACT_GET_INTEGRAL_TIME
                  << ACT_GET_SPECTRUM
                  << ACT_GET_RAM;
    protocol = HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection")->value("Spec");
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HSpecStrategy::HSpecStrategy(QObject *parent) :
    HAbstractActionStrategy(*new HSpecStrategyPrivate, parent)
{
}

HSpecStrategy::HSpecStrategy(HSpecStrategyPrivate &p, QObject *parent) :
    HAbstractActionStrategy(p, parent)
{
}

HSpecStrategy::~HSpecStrategy()
{
    qDebug() << __func__;
}

QString HSpecStrategy::typeName()
{
    return "HSpecStrategy";
}

HErrorType HSpecStrategy::handle(HActionType action)
{
    Q_D(HSpecStrategy);
    uint i;
    QVector<uchar> ubuff;
    QVector<double> dbuff;
    HErrorType error;

    switch(action)
    {
    case ACT_SET_INTEGRAL_TIME:
        return d->protocol->setData(action, uint(d->testSpec->data("[积分时间]").toDouble() * 500));
    case ACT_SET_SPECTRUM_AVG_TIMES:
        return d->protocol->setData(action, d->testSpec->data("[光谱平均次数]").toInt());
    case ACT_SET_SPECTRUM_SAMPLE_DELAY:
        return d->protocol->setData(action, d->testSpec->data("[光谱采样延时]").toInt());
    case ACT_GET_INTEGRAL_TIME:
        error = d->protocol->getData(action, i);
        if (error == E_OK)
            d->testSpec->setData("[积分时间]", i / 500.0);
        return error;
    case ACT_GET_SPECTRUM:
        error = d->protocol->getData(action, dbuff);//d->testSpec->data("[光谱采样等待时间]").toInt());
        if (error == E_OK)
            d->testSpec->setSample(dbuff, true);
        return error;
    case ACT_SET_RAM:
        return d->protocol->setData(action, d->testSpec->getRam());
    case ACT_GET_RAM:
        error = d->protocol->getData(action, ubuff);
        if (error == E_OK)
        {
            if (!d->testSpec->setRam(ubuff))
                error = E_DEVICE_DATA_RETURN_ERROR;
        }
        return error;
    }
    return E_OK;
}

HE_CONTROLLER_END_NAMESPACE
