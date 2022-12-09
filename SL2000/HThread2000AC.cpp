#include "HThread2000AC_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeController/IControllerFactory.h"
#include "HeController/IActionStrategy.h"

HThread2000ACPrivate::HThread2000ACPrivate()
{
    actionSupport << ACT_INTEGRATE_TEST;
}

HThread2000AC::HThread2000AC(QObject *parent) :
    HAbstractThread(*new HThread2000ACPrivate, parent)
{
    init();
}

HThread2000AC::~HThread2000AC() = default;

QString HThread2000AC::typeName()
{
    return "HThread2000AC";
}

QString HThread2000AC::threadInfo()
{
    return tr("线程");
}

bool HThread2000AC::handleAction(HActionType action)
{
    Q_D(HThread2000AC);
    if (action == ACT_INTEGRATE_TEST)
    {
        if (!d->strategyElec->handle(ACT_GET_ELEC_DATA) || !d->strategySpec->handle(ACT_GET_SPECTRUM))
            return false;
        auto f = d->testData->data("[光谱光通量]").toDouble();
        auto p = d->testData->data("[交流电功率]").toDouble();
        auto x = d->testData->data("[光合光子通量效率]").toDouble();
        auto y = d->testData->data("[荧光效能]").toDouble();
        d->testData->setData("[光效率]", p < 0.0001 ? 0.0 :  f / p);
        d->testData->setData("[光合光子通量效率]", p < 0.00001 ? x :  x / p);
        d->testData->setData("[荧光效能]", p < 0.00001 ? y :  y / p);
        return true;
    }
    return HAbstractThread::handleAction(action);
}

void HThread2000AC::init()
{
    Q_D(HThread2000AC);
    auto factory = HAppContext::getContextPointer<IControllerFactory>("IControllerFactory");
    auto protocolCollection = HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection");
    d->protocolSpec = protocolCollection->value("Spec");
    d->protocolElec = protocolCollection->value("Elec");
    d->strategySpec = factory->createStrategy("HSpecStrategy", this);
    d->strategyElec = factory->createStrategy("HPowerFactorStrategy", this);
    d->strategySpec->setProtocol(d->protocolSpec);
    d->strategyElec->setProtocol(d->protocolElec);
    d->protocols << d->protocolSpec << d->protocolElec;
    d->strategys << d->strategySpec << d->strategyElec;
}
