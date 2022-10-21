#include "HSpecStrategy_p.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HException.h"
#include "HeData/ITestSpec.h"
#include "HeCommunicate/IProtocol.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HSpecStrategyPrivate::HSpecStrategyPrivate()
{
    actionSupport << ACT_SET_INTEGRAL_TIME
                  << ACT_SET_SPECTRUM_AVG_TIMES
                  << ACT_SET_SPECTRUM_SAMPLE_DELAY
                  << ACT_SET_RAM
                  << ACT_GET_INTEGRAL_TIME
                  << ACT_GET_SPECTRUM
                  << ACT_GET_RAM;
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

HSpecStrategy::~HSpecStrategy() = default;

QString HSpecStrategy::typeName()
{
    return "HSpecStrategy";
}

bool HSpecStrategy::handle(HActionType action)
{
    Q_D(HSpecStrategy);
    uint i;
    QVector<uchar> ubuff;
    QVector<double> dbuff;

    switch(action)
    {
    case ACT_SET_INTEGRAL_TIME:
        return d->protocol->setData(action, uint(d->testSpec->data("[积分时间]").toDouble() * 1000));
    case ACT_SET_SPECTRUM_AVG_TIMES:
        return d->protocol->setData(action, d->testSpec->data("[光谱平均次数]").toInt());
    case ACT_SET_SPECTRUM_SAMPLE_DELAY:
        return d->protocol->setData(action, d->testSpec->data("[光谱采样延时]").toInt());
    case ACT_GET_INTEGRAL_TIME:
        d->protocol->getData(action, i);
        d->testSpec->setData("[积分时间]", i / 500.0);
        return true;
    case ACT_GET_SPECTRUM:
        d->protocol->getData(action, dbuff);//d->testSpec->data("[光谱采样等待时间]").toInt());
        d->testSpec->setSample(dbuff, true);
        return true;
    case ACT_SET_RAM:
        return d->protocol->setData(action, d->testSpec->getRam());
    case ACT_GET_RAM:
        d->protocol->getData(action, ubuff);
        if (!d->testSpec->setRam(ubuff))
            throw HException(E_DEVICE_DATA_RETURN_ERROR);
        return true;
    }
    return false;
}

HE_END_NAMESPACE
