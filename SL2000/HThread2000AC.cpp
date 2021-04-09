#include "HThread2000AC_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeController/IControllerFactory.h"
#include "HeController/IActionStrategy.h"
#include <QtCore/QDebug>

HThread2000ACPrivate::HThread2000ACPrivate()
{
    actionSupport << ACT_GET_SPECTRUM_ELEC;
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
    auto protocolCollection = HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection");
    protocolSpec = protocolCollection->value("Spec");
    protocolElec = protocolCollection->value("Elec");
    protocols << protocolSpec << protocolElec;
}

HThread2000AC::HThread2000AC(QObject *parent) :
    HAbstractThread(*new HThread2000ACPrivate, parent)
{
    init();
}


HThread2000AC::~HThread2000AC()
{
    qDebug() << __func__;
}

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
    if (action == ACT_GET_SPECTRUM_ELEC)
    {
        if (!d->strategyElec->handle(ACT_GET_ELEC_DATA) || !d->strategySpec->handle(ACT_GET_SPECTRUM))
            return false;
        auto f = d->testData->data("[光谱光通量]").toDouble();
        auto p = d->testData->data("[交流电功率]").toDouble();
        d->testData->setData("[光效率]", p < 0.0001 ? 0.0 :  f / p);
        return true;
    }
    return HAbstractThread::handleAction(action);
}

void HThread2000AC::init()
{
    Q_D(HThread2000AC);
    auto factory = HAppContext::getContextPointer<IControllerFactory>("IControllerFactory");
    d->strategySpec = factory->createStrategy("HSpecStrategy", this);
    d->strategyElec = factory->createStrategy("HPowerFactorStrategy", this);
    d->strategySpec->setProtocol(d->protocolSpec);
    d->strategyElec->setProtocol(d->protocolElec);
    d->strategys << d->strategySpec << d->strategyElec;
}
