#include "HSpecElecThread_p.h"
#include "IControllerFactory.h"
#include "IActionStrategy.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include <QtCore/QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HSpecElecThreadPrivate::HSpecElecThreadPrivate()
{
    actionSupport << ACT_SINGLE_TEST
                  << ACT_GET_SPECTRUM_ELEC;
    auto protocolCollection = HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection");
    protocolSpec = protocolCollection->value("Spec");
    protocolElse = protocolCollection->value("Else");
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
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
        error = d->strategyElec->handle(ACT_GET_ELEC_DATA);
        if (error != E_OK)
            return error;
        error = getSpectrum(d->testData->data("[光谱平均次数]").toInt());
        if (error != E_OK)
            return error;
        error = d->strategyElec->handle(ACT_SET_SOURCE_MODE);
        if (error != E_OK)
            return error;
        handleData();
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
        handleData();
        return E_OK;
    }
    return HAbstractThread::handleAction(action);
}

HErrorType HSpecElecThread::getSpectrum(int n)
{
    Q_D(HSpecElecThread);
    int i,j;
    HErrorType error;
    QVector<double> sample1, samples2;

    n = qMin(1, n);
    for (i = 0; i < n; i++)
    {
        error = d->protocolSpec->getData(ACT_GET_SPECTRUM, samples2);
        if (error != E_OK)
            return error;
        if (sample1.size() < samples2.size())
            sample1.resize(samples2.size());
        for (j = 0; j < samples2.size(); j++)
            sample1[j] += 1.0 * samples2.at(j) / n;
    }
    d->testData->setData("[光谱采样值]", QVariant::fromValue(sample1));
    return E_OK;
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

HE_CONTROLLER_END_NAMESPACE
