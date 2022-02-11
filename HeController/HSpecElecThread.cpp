#include "HSpecElecThread_p.h"
#include "IControllerFactory.h"
#include "IActionStrategy.h"
#include "HControllerHelper.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"

HE_BEGIN_NAMESPACE

HSpecElecThreadPrivate::HSpecElecThreadPrivate()
{
    actionSupport << ACT_SINGLE_TEST
                  << ACT_GET_SPECTRUM_ELEC;
    auto protocolCollection = HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection");
    protocolSpec = protocolCollection->value("Spec");
    protocolElse = protocolCollection->value("Else");
    protocols << protocolSpec << protocolElse;
}

HSpecElecThread::HSpecElecThread(QObject *parent) :
    HAbstractThread(*new HSpecElecThreadPrivate, parent)
{
    init();
}

HSpecElecThread::HSpecElecThread(HSpecElecThreadPrivate &p, QObject *parent) :
    HAbstractThread(p, parent)
{
}

HSpecElecThread::~HSpecElecThread() = default;

QString HSpecElecThread::typeName()
{
    return "HSpecElecThread";
}

QString HSpecElecThread::threadInfo()
{
    return tr("线程");
}

bool HSpecElecThread::handleAction(HActionType action)
{
    Q_D(HSpecElecThread);

    switch(action)
    {
    case ACT_SINGLE_TEST:
        d->strategyElec->handle(ACT_GET_ELEC_DATA);
        msleep(d->testData->data("[光谱采样延时]").toInt());
        HControllerHelper::multGetSpectrum(d->protocolSpec, d->testData, d->testData->data("[光谱平均次数]").toInt());
        d->strategyElec->handle(ACT_SET_SOURCE_MODE);
        handleData();
        return true;
    case ACT_GET_SPECTRUM_ELEC:
        d->strategyElec->handle(ACT_GET_MEASURED_VOLTAGE);
        d->strategyElec->handle(ACT_GET_MEASURED_CURRENT);
        d->strategySpec->handle(ACT_GET_SPECTRUM);
        handleData();
        return true;
    }
    return HAbstractThread::handleAction(action);
}

void HSpecElecThread::handleData()
{
    Q_D(HSpecElecThread);
    auto f = d->testData->data("[光谱光通量]").toDouble();
    auto p = d->testData->data("[电功率]").toDouble();
    d->testData->setData("[光效率]", p < 0.0001 ? 0.0 :  f / p);
}

void HSpecElecThread::init()
{
    Q_D(HSpecElecThread);
    auto factory = HAppContext::getContextPointer<IControllerFactory>("IControllerFactory");
    d->strategySpec = factory->createStrategy("HSpecStrategy", this);
    d->strategyElec = factory->createStrategy("HElecStrategy", this);
    d->strategySpec->setProtocol(d->protocolSpec);
    d->strategyElec->setProtocol(d->protocolElse);
    d->strategys << d->strategySpec << d->strategyElec;
}

HE_END_NAMESPACE
