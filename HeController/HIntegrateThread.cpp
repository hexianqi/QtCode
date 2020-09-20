#include "HIntegrateThread_p.h"
#include "IControllerFactory.h"
#include "IActionStrategy.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include <QtCore/QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HIntegrateThreadPrivate::HIntegrateThreadPrivate()
{
    actionSupport << ACT_SINGLE_TEST
                  << ACT_GET_SPECTRUM_ELEC;
    auto protocolCollection = HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection");
    protocolSpec = protocolCollection->value("Spec");
    protocolElse = protocolCollection->value("Else");
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
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
    init();
}

HIntegrateThread::~HIntegrateThread()
{
    qDebug() << __func__;
}

QString HIntegrateThread::typeName()
{
    return "HIntegrateThread";
}

QString HIntegrateThread::threadInfo()
{
    return tr("综合线程");
}

HErrorType HIntegrateThread::handleAction(HActionType action)
{
    Q_D(HIntegrateThread);
    HErrorType error;

    switch(action)
    {
    case ACT_SINGLE_TEST:
        error = d->strategyElec->handle(ACT_GET_ELEC_DATA);
        if (error != E_OK)
            return error;
        msleep(d->testData->data("[光谱采样延时]").toInt());
        error = d->strategyLuminous->handle(ACT_GET_LUMINOUS_DATA);
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
        if (d->testData->data("[预配置测试]").toBool())
        {
            d->testData->setData("[电源模式]", 2);
            error = d->strategyElec->handle(ACT_SET_SOURCE_MODE);
            if (error != E_OK)
                return error;
            error = d->strategyElec->handle(ACT_GET_REVERSE_CURRENT);
            if (error != E_OK)
                return error;
            d->testData->setData("[电源模式]", 1);
            error = d->strategyElec->handle(ACT_SET_SOURCE_MODE);
            if (error != E_OK)
                return error;
            d->testData->setData("[预配置测试]", false);
        }
        error = d->strategyElec->handle(ACT_GET_MEASURED_VOLTAGE);
        if (error != E_OK)
            return error;
        error = d->strategyElec->handle(ACT_GET_MEASURED_CURRENT);
        if (error != E_OK)
            return error;
        error = d->strategyLuminous->handle(ACT_GET_LUMINOUS_DATA);
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

HErrorType HIntegrateThread::getSpectrum(int n)
{
    Q_D(HIntegrateThread);
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

void HIntegrateThread::handleData()
{
    Q_D(HIntegrateThread);
    if (!d->testData->data("[使用光探头]").toBool() || d->testData->data("[光测试类型]").toString() != "[光通量]")
        d->testData->setData("[光通量]", d->testData->data("[光谱光通量]"));
    auto f = d->testData->data("[光通量]").toDouble();
    auto p = d->testData->data("[电功率]").toDouble();
    auto e = d->testData->data("[明视觉光效率]").toDouble();
    d->testData->setData("[光效率]", p < 0.00001 ? 0.0 :  f / p);
    d->testData->setData("[光功率]", e < 0.00001 ? 0.0 : 1000 * f / e);
}

void HIntegrateThread::init()
{
    Q_D(HIntegrateThread);
    auto factory = HAppContext::getContextPointer<IControllerFactory>("IControllerFactory");
    d->strategySpec = factory->createStrategy("HSpecStrategy", this);
    d->strategyElec = factory->createStrategy("HElecStrategy", this);
    d->strategyLuminous = factory->createStrategy("HLuminousStrategy", this);
    d->strategySpec->setProtocol(d->protocolSpec);
    d->strategyElec->setProtocol(d->protocolElse);
    d->strategyLuminous->setProtocol(d->protocolElse);
    d->strategys << d->strategySpec << d->strategyElec << d->strategyLuminous;
}


HE_CONTROLLER_END_NAMESPACE
