#include "HThread2100DC_p.h"
#include "HDaXinStrategy.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeController/IControllerFactory.h"
#include "HeController/HControllerHelper.h"

HThread2100DCPrivate::HThread2100DCPrivate()
{
    actionSupport << ACT_SINGLE_TEST
                  << ACT_INTEGRATE_TEST;
    auto protocolCollection = HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection");
    protocolSpec = protocolCollection->value("Spec");
    protocolElec = protocolCollection->value("Elec");
    protocols << protocolSpec << protocolElec;
}

HThread2100DC::HThread2100DC(QObject *parent) :
    HAbstractThread(*new HThread2100DCPrivate, parent)
{
    init();
}

HThread2100DC::~HThread2100DC() = default;

QString HThread2100DC::typeName()
{
    return "HThread2100DC";
}

QString HThread2100DC::threadInfo()
{
    return tr("线程");
}

bool HThread2100DC::handleAction(HActionType action)
{
    Q_D(HThread2100DC);

    switch(action)
    {
    case ACT_SINGLE_TEST:
        d->testData->setData("[电源模式]", 1);
        d->strategyElec->handle(ACT_SET_SOURCE_MODE);
        msleep(1000);
        d->strategyElec->handle(ACT_GET_ELEC_DATA);
        msleep(d->testData->data("[光谱采样延时]").toInt());
        HControllerHelper::multGetSpectrum(d->protocolSpec, d->testData, d->testData->data("[光谱平均次数]").toInt());
        d->testData->setData("[电源模式]", 0);
        d->strategyElec->handle(ACT_SET_SOURCE_MODE);
        handleData();
        return true;
    case ACT_INTEGRATE_TEST:
        d->strategyElec->handle(ACT_GET_ELEC_DATA);
        d->strategySpec->handle(ACT_GET_SPECTRUM);
        handleData();
        return true;
    }
    return HAbstractThread::handleAction(action);
}

void HThread2100DC::handleData()
{
    Q_D(HThread2100DC);
    auto f = d->testData->data("[光谱光通量]").toDouble();
    auto p = d->testData->data("[电功率]").toDouble();
    auto x = d->testData->data("[光合光子通量效率]").toDouble();
    auto y = d->testData->data("[荧光效能]").toDouble();
    d->testData->setData("[光效率]", p < 0.00001 ? 0.0 :  f / p);
    d->testData->setData("[光合光子通量效率]", p < 0.00001 ? x :  x / p);
    d->testData->setData("[荧光效能]", p < 0.00001 ? y :  y / p);
}

void HThread2100DC::init()
{
    Q_D(HThread2100DC);
    auto factory = HAppContext::getContextPointer<IControllerFactory>("IControllerFactory");
    d->strategySpec = factory->createStrategy("HSpecStrategy", this);
    d->strategyElec = new HDaXinStrategy(this);
    d->strategySpec->setProtocol(d->protocolSpec);
    d->strategyElec->setProtocol(d->protocolElec);
    d->strategys << d->strategySpec << d->strategyElec;
}
