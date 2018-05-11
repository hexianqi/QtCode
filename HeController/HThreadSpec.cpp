#include "HThreadSpec_p.h"
#include "IModel.h"
#include "ITestSpec.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/ICommunicateFactory.h"
#include "HeCommunicate/IProtocol.h"
#include <QVector>

HE_CORE_USE_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

void HThreadSpecPrivate::init()
{
    actionSupport = QList<HActionType>()
            << ACT_SET_INTEGRAL_TIME
            << ACT_SET_SPECTRUM_AVG_TIMES
            << ACT_SET_SPECTRUM_SAMPLE_DELAY
            << ACT_GET_INTEGRAL_TIME
            << ACT_GET_SPECTRUM;

    QVariantMap param;
    param.insert("device", ToVariant(model->device("Spec")));

    testSpec = hContextPointer(ITestSpec, "ITestSpec");
    protocolSpec =  hContextPointer(ICommunicateFactory, "ICommunicateFactory")->createProtocol("Spec", param);
    protocols.insert("Spec", protocolSpec);
}

HThreadSpec::HThreadSpec(IModel *model, QObject *parent)
    : HAbstractThread(model, parent)
{
    Q_D(HThreadSpec);
    d->q_ptr = this;
    d->init();
}

HThreadSpec::HThreadSpec(HThreadSpecPrivate &p, QObject *parent)
    : HAbstractThread(p, parent)
{
    Q_D(HThreadSpec);
    d->q_ptr = this;
    d->init();
}

HThreadSpec::~HThreadSpec()
{
}

QString HThreadSpec::threadInfo()
{
    return tr("光谱线程");
}

HErrorType HThreadSpec::handleAction(HActionType action)
{
    Q_D(HThreadSpec);
    uint i;
    QVector<double> t;
    HErrorType error;

    switch(action)
    {
    case ACT_SET_INTEGRAL_TIME:
        error = d->protocolSpec->setData(action, uint(d->testSpec->testData("[积分时间]").toDouble() * 500));
        if (error == E_OK)
            d->testSpec->clearQueue();
        return error;
    case ACT_SET_SPECTRUM_AVG_TIMES:
        return d->protocolSpec->setData(action, d->testSpec->testData("[光谱平均次数]").toInt());
    case ACT_SET_SPECTRUM_SAMPLE_DELAY:
        return d->protocolSpec->setData(action, d->testSpec->testData("[光谱采样延时]").toInt());
    case ACT_GET_INTEGRAL_TIME:
        error = d->protocolSpec->getData(action, i);
        if (error == E_OK)
            d->testSpec->setTestData("[积分时间]", i / 500.0);
        return error;
    case ACT_GET_SPECTRUM:
        error = d->protocolSpec->getData(action, t, d->testSpec->testData("[光谱采样等待时间]").toInt());
        if (error == E_OK)
            d->testSpec->setSample(t, true);
        return error;
    }
    return E_THREAD_NO_HANDLE;
}
