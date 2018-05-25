#include "HThreadSpec_p.h"
#include "ITestSpec.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include <QVector>
#include <QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HThreadSpecPrivate::HThreadSpecPrivate(HThreadSpec *q)
    : HAbstractThreadPrivate(q)
{
    actionSupport = QList<HActionType>()
            << ACT_SET_INTEGRAL_TIME
            << ACT_SET_SPECTRUM_AVG_TIMES
            << ACT_SET_SPECTRUM_SAMPLE_DELAY
            << ACT_GET_INTEGRAL_TIME
            << ACT_GET_SPECTRUM;

    protocolSpec = HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection")->value("Spec");
    Q_ASSERT(protocolSpec != nullptr);
    protocols.insert("Spec", protocolSpec);
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
    Q_ASSERT(testSpec != nullptr);
}

HThreadSpec::HThreadSpec(QObject *parent)
    : HAbstractThread(*new HThreadSpecPrivate(this), parent)
{
}

HThreadSpec::HThreadSpec(HThreadSpecPrivate &p, QObject *parent)
    : HAbstractThread(p, parent)
{
}

HThreadSpec::~HThreadSpec()
{
    qDebug() << "HThreadSpec Destroy";
}

QString HThreadSpec::typeName()
{
    return "HThreadSpec";
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
        error = d->protocolSpec->setData(action, uint(d->testSpec->data("[积分时间]").toDouble() * 500));
        if (error == E_OK)
            d->testSpec->clearQueue();
        return error;
    case ACT_SET_SPECTRUM_AVG_TIMES:
        return d->protocolSpec->setData(action, d->testSpec->data("[光谱平均次数]").toInt());
    case ACT_SET_SPECTRUM_SAMPLE_DELAY:
        return d->protocolSpec->setData(action, d->testSpec->data("[光谱采样延时]").toInt());
    case ACT_GET_INTEGRAL_TIME:
        error = d->protocolSpec->getData(action, i);
        if (error == E_OK)
            d->testSpec->setData("[积分时间]", i / 500.0);
        return error;
    case ACT_GET_SPECTRUM:
        error = d->protocolSpec->getData(action, t, d->testSpec->data("[光谱采样等待时间]").toInt());
        if (error == E_OK)
            d->testSpec->setSample(t, true);
        return error;
    }
    return E_THREAD_NO_HANDLE;
}

HE_CONTROLLER_END_NAMESPACE

