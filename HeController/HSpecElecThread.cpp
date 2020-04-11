#include "HSpecElecThread_p.h"
#include "IControllerFactory.h"
#include "IActionStrategy.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestSpec.h"
#include "HeData/ITestElec.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include <QtCore/QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HSpecElecThreadPrivate::HSpecElecThreadPrivate()
{
    actionSupport << ACT_SINGLE_TEST
                  << ACT_GET_SPECTRUM_ELEC;
    auto protocolCollection = HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection");
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
    testElec = HAppContext::getContextPointer<ITestElec>("ITestElec");
    protocols.insert("Spec", protocolCollection->value("Spec"));
    protocols.insert("Elec", protocolCollection->value("Elec"));
}

HSpecElecThread::HSpecElecThread(QObject *parent) :
    HAbstractThread(*new HSpecElecThreadPrivate, parent)
{
    init();
}

HSpecElecThread::HSpecElecThread(HSpecElecThreadPrivate &p, QObject *parent) :
    HAbstractThread(p, parent)
{
    init();
}

HSpecElecThread::~HSpecElecThread()
{
    qDebug() << __func__;
}

QString HSpecElecThread::typeName()
{
    return "HSpecElecThread";
}

QString HSpecElecThread::threadInfo()
{
    return tr("光谱&电线程");
}

HErrorType HSpecElecThread::handleAction(HActionType action)
{
    Q_D(HSpecElecThread);
    HErrorType error;

    switch(action)
    {
    case ACT_SINGLE_TEST:
        error = d->strategyElec->handle(ACT_GET_ELEC_PARAM);
        if (error != E_OK)
            return error;
        error = d->strategySpec->handle(ACT_GET_SPECTRUM);
        if (error != E_OK)
            return error;
        error = d->strategyElec->handle(ACT_SET_SOURCE_MODE);
        if (error != E_OK)
            return error;
        setEfficacy();
        return E_OK;
    case ACT_GET_SPECTRUM_ELEC:
        error = d->strategyElec->handle(ACT_GET_MEASURED_VOLTAGE);
        if (error != E_OK)
            return error;
        error = d->strategyElec->handle(ACT_GET_MEASURED_CURRENT);
        if (error != E_OK)
            return error;
        error = d->strategySpec->handle(ACT_GET_SPECTRUM);
        if (error != E_OK)
            return error;
        setEfficacy();
        return E_OK;
    }
    return HAbstractThread::handleAction(action);
}

void HSpecElecThread::setEfficacy()
{
    Q_D(HSpecElecThread);
    auto l = d->testSpec->data("[光谱光通量]").toDouble();
    auto p = d->testElec->data("[电功率]").toDouble();
    d->testSpec->setData("[光效率]", p < 0.01 ? 0.0 :  l / p);
}

void HSpecElecThread::init()
{
    Q_D(HSpecElecThread);
    auto factory = HAppContext::getContextPointer<IControllerFactory>("IControllerFactory");
    d->strategySpec = factory->createStrategy("HSpecStrategy", this);
    d->strategyElec = factory->createStrategy("HElecStrategy", this);
    d->strategys.insert("Spec", d->strategySpec);
    d->strategys.insert("Elec", d->strategyElec);
}

HE_CONTROLLER_END_NAMESPACE
