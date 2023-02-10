#include "HThread1000RGB_p.h"
#include "HStrategy1000RGB.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeController/IControllerFactory.h"
#include "HeController/HControllerHelper.h"
#include "HeData/ITestData.h"

HThread1000RGBPrivate::HThread1000RGBPrivate()
{
    actionSupport << ACT_SINGLE_TEST
                  << ACT_INTEGRATE_TEST;
}

HThread1000RGB::HThread1000RGB(QObject *parent) :
    HAbstractThread(*new HThread1000RGBPrivate, parent)
{
    init();
}

HThread1000RGB::~HThread1000RGB() = default;

QString HThread1000RGB::typeName()
{
    return "HThread1000RGB";
}

QString HThread1000RGB::threadInfo()
{
    return tr("线程");
}

bool HThread1000RGB::handleAction(HActionType action)
{
    Q_D(HThread1000RGB);
    switch(action)
    {
    case ACT_SINGLE_TEST:
        d->strategyElec->handle(ACT_GET_ELEC_DATA);
        msleep(d->testData->data("[光谱采样延时]").toInt());
        d->strategyLuminous->handle(ACT_GET_LUMINOUS_DATA);
        HControllerHelper::multGetSpectrum(d->protocolSpec, d->testData, d->testData->data("[光谱平均次数]").toInt());
        d->testData->setData("[电源模式]", 0);
        d->strategyElec->handle(ACT_SET_SOURCE_MODE);
        handleData();
        return true;
    case ACT_INTEGRATE_TEST:
        if (d->testData->data("[预配置测试]").toBool())
        {
            d->testData->setData("[电源模式]", 2);
            d->strategyElec->handle(ACT_SET_SOURCE_MODE);
            d->strategyElec->handle(ACT_GET_REVERSE_CURRENT);
            d->testData->setData("[电源模式]", 1);
            d->strategyElec->handle(ACT_SET_SOURCE_MODE);
            d->testData->setData("[预配置测试]", false);
        }
        d->strategyElec->handle(ACT_GET_MEASURED_VOLTAGE);
        d->strategyElec->handle(ACT_GET_MEASURED_CURRENT);
        d->strategyLuminous->handle(ACT_GET_LUMINOUS_DATA);
        d->strategySpec->handle(ACT_GET_SPECTRUM);
        handleData();
        return true;
    }
    return HAbstractThread::handleAction(action);
}

void HThread1000RGB::handleData()
{
    Q_D(HThread1000RGB);
    auto f = d->testData->data("[光谱光通量]").toDouble();
    auto p = d->testData->data("[电功率]").toDouble();
    auto e = d->testData->data("[明视觉光效率]").toDouble();
    auto x = d->testData->data("[光合光子通量效率]").toDouble();
    auto y = d->testData->data("[荧光效能]").toDouble();
    d->testData->setData("[光通量]", f);
    d->testData->setData("[光效率]", p < 0.00001 ? 0.0 :  f / p);
    d->testData->setData("[光功率]", e < 0.00001 ? 0.0 : 1000 * f / e);
    d->testData->setData("[光合光子通量效率]", p < 0.00001 ? x :  x / p);
    d->testData->setData("[荧光效能]", p < 0.00001 ? y :  y / p);
}

void HThread1000RGB::init()
{
    Q_D(HThread1000RGB);
    auto factory = HAppContext::getContextPointer<IControllerFactory>("IControllerFactory");
    auto protocolCollection = HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection");
    d->protocolSpec = protocolCollection->value("Spec");
    d->protocolElse = protocolCollection->value("Else");
    d->strategySpec = factory->createStrategy("HSpecStrategy", this);
    d->strategyElec = new HStrategy1000RGB(this);
    d->strategyLuminous = factory->createStrategy("HLuminousStrategy", this);
    d->strategySpec->setProtocol(d->protocolSpec);
    d->strategyElec->setProtocol(d->protocolElse);
    d->strategyLuminous->setProtocol(d->protocolElse);
    d->protocols << d->protocolSpec << d->protocolElse;
    d->strategys << d->strategySpec << d->strategyElec << d->strategyLuminous;
}




