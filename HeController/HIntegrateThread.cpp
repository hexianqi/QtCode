#include "HIntegrateThread_p.h"
#include "IControllerFactory.h"
#include "IActionStrategy.h"
#include "HControllerHelper.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"

HE_BEGIN_NAMESPACE

HIntegrateThreadPrivate::HIntegrateThreadPrivate()
{
    actionSupport << ACT_SINGLE_TEST
                  << ACT_GET_SPECTRUM_ELEC;
    auto protocolCollection = HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection");
    protocolSpec = protocolCollection->value("Spec");
    protocolElse = protocolCollection->value("Else");
    protocols << protocolSpec << protocolElse;
}

HIntegrateThread::HIntegrateThread(QObject *parent) :
    HAbstractThread(*new HIntegrateThreadPrivate, parent)
{
    init();
}

HIntegrateThread::HIntegrateThread(HIntegrateThreadPrivate &p, QObject *parent) :
    HAbstractThread(p, parent)
{
}

HIntegrateThread::~HIntegrateThread() = default;

QString HIntegrateThread::typeName()
{
    return "HIntegrateThread";
}

QString HIntegrateThread::threadInfo()
{
    return tr("线程");
}

bool HIntegrateThread::handleAction(HActionType action)
{
    Q_D(HIntegrateThread);

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
    case ACT_GET_SPECTRUM_ELEC:
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

void HIntegrateThread::handleData()
{
    Q_D(HIntegrateThread);
    if (!d->testData->data("[使用光探头]").toBool() || d->testData->data("[光测试类型]").toString() != "[光通量]")
        d->testData->setData("[光通量]", d->testData->data("[光谱光通量]"));
    auto f = d->testData->data("[光通量]").toDouble();
    auto p = d->testData->data("[电功率]").toDouble();
    auto e = d->testData->data("[明视觉光效率]").toDouble();
    auto x = d->testData->data("[光合光子通量效率]").toDouble();
    auto y = d->testData->data("[荧光效能]").toDouble();
    d->testData->setData("[光效率]", p < 0.00001 ? 0.0 :  f / p);
    d->testData->setData("[光功率]", e < 0.00001 ? 0.0 : 1000 * f / e);
    d->testData->setData("[光合光子通量效率]", p < 0.00001 ? x :  x / p);
    d->testData->setData("[荧光效能]", p < 0.00001 ? y :  y / p);
}

void HIntegrateThread::init()
{
    Q_D(HIntegrateThread);
    auto factory = HAppContext::getContextPointer<IControllerFactory>("IControllerFactory");
    d->strategySpec = factory->createStrategy("HSpecStrategy", this);
    d->strategyElec = factory->createStrategy("HElecStrategy", this);
    d->strategyLuminous = factory->createStrategy("HLuminousStrategy", this);
    d->strategyMotor = factory->createStrategy("HMotorStrategy", this);
    d->strategySpec->setProtocol(d->protocolSpec);
    d->strategyElec->setProtocol(d->protocolElse);
    d->strategyLuminous->setProtocol(d->protocolElse);
    d->strategyMotor->setProtocol(d->protocolElse);
    d->strategys << d->strategySpec << d->strategyElec << d->strategyLuminous << d->strategyMotor;
}

HE_END_NAMESPACE
