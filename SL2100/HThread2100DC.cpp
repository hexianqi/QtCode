#include "HThread2100DC_p.h"
#include "HDaXinStrategy.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeController/IControllerFactory.h"
#include <QtCore/QDebug>

HThread2100DCPrivate::HThread2100DCPrivate()
{
    actionSupport << ACT_SINGLE_TEST
                  << ACT_GET_SPECTRUM_ELEC;
    auto protocolCollection = HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection");
    protocolSpec = protocolCollection->value("Spec");
    protocolElse = protocolCollection->value("Else");
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
    protocols << protocolSpec << protocolElse;
}

HThread2100DC::HThread2100DC(QObject *parent) :
    HAbstractThread(*new HThread2100DCPrivate, parent)
{
    init();
}

HThread2100DC::~HThread2100DC()
{
    qDebug() << __func__;
}

QString HThread2100DC::typeName()
{
    return "HThread2100DC";
}

QString HThread2100DC::threadInfo()
{
    return tr("综合线程");
}

bool HThread2100DC::handleAction(HActionType action)
{
    Q_D(HThread2100DC);

    switch(action)
    {
    case ACT_SINGLE_TEST:
        d->testData->setData("[电源模式]", 1);
        d->strategyElec->handle(ACT_SET_SOURCE_MODE);
        d->strategyElec->handle(ACT_GET_ELEC_DATA);
        msleep(d->testData->data("[光谱采样延时]").toInt());
        getSpectrum(d->testData->data("[光谱平均次数]").toInt());
        d->testData->setData("[电源模式]", 0);
        d->strategyElec->handle(ACT_SET_SOURCE_MODE);
        handleData();
        return true;
    case ACT_GET_SPECTRUM_ELEC:
        d->strategyElec->handle(ACT_GET_ELEC_DATA);
        d->strategySpec->handle(ACT_GET_SPECTRUM);
        handleData();
        return true;
    }
    return HAbstractThread::handleAction(action);
}

void HThread2100DC::getSpectrum(int n)
{
    Q_D(HThread2100DC);
    int i,j;
    QVector<double> sample1, samples2;

    n = qMin(1, n);
    for (i = 0; i < n; i++)
    {
        d->protocolSpec->getData(ACT_GET_SPECTRUM, samples2);
        if (sample1.size() < samples2.size())
            sample1.resize(samples2.size());
        for (j = 0; j < samples2.size(); j++)
            sample1[j] += 1.0 * samples2.at(j) / n;
    }
    d->testData->setData("[光谱采样值]", QVariant::fromValue(sample1));
}

void HThread2100DC::handleData()
{
    Q_D(HThread2100DC);
    auto f = d->testData->data("[光谱光通量]").toDouble();
    auto p = d->testData->data("[电功率]").toDouble();
    d->testData->setData("[光效率]", p < 0.0001 ? 0.0 :  f / p);
}

void HThread2100DC::init()
{
    Q_D(HThread2100DC);
    auto factory = HAppContext::getContextPointer<IControllerFactory>("IControllerFactory");
    d->strategySpec = factory->createStrategy("HSpecStrategy", this);
    d->strategyElec = new HDaXinStrategy(this);
    d->strategySpec->setProtocol(d->protocolSpec);
    d->strategyElec->setProtocol(d->protocolElse);
    d->strategys << d->strategySpec << d->strategyElec;
}
