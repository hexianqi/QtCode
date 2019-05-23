#include "HSpecThread_p.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeData/ITestSpec.h"
#include <QtCore/QVector>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HSpecThreadPrivate::HSpecThreadPrivate()
{
    actionSupport << ACT_SET_INTEGRAL_TIME
                  << ACT_SET_SPECTRUM_AVG_TIMES
                  << ACT_SET_SPECTRUM_SAMPLE_DELAY
                  << ACT_SET_RAM
                  << ACT_GET_INTEGRAL_TIME
                  << ACT_GET_SPECTRUM
                  << ACT_GET_RAM;
    protocolSpec = HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection")->value("Spec");
    protocols.insert("Spec", protocolSpec);
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HSpecThread::HSpecThread(QObject *parent) :
    HAbstractThread(*new HSpecThreadPrivate, parent)
{
}

HSpecThread::HSpecThread(HSpecThreadPrivate &p, QObject *parent) :
    HAbstractThread(p, parent)
{
}

HSpecThread::~HSpecThread()
{
    qDebug() << __func__;
}

QString HSpecThread::typeName()
{
    return "HSpecThread";
}

QString HSpecThread::threadInfo()
{
    return tr("光谱线程");
}

HErrorType HSpecThread::handleAction(HActionType action)
{
    Q_D(HSpecThread);
    uint i;
    QVector<uchar> buff;
    QVector<double> t;
    HErrorType error;

    switch(action)
    {
    case ACT_SET_INTEGRAL_TIME:
        return d->protocolSpec->setData(action, uint(d->testSpec->data("[积分时间]").toDouble() * 500));
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
        error = d->protocolSpec->getData(action, t);//d->testSpec->data("[光谱采样等待时间]").toInt());
        if (error == E_OK)
            d->testSpec->setSample(t, true);
        return error;
    case ACT_SET_RAM:
        return d->protocolSpec->setData(action, d->testSpec->getRam());
    case ACT_GET_RAM:
        error = d->protocolSpec->getData(action, buff);
        if (error == E_OK)
        {
            if (!d->testSpec->setRam(buff))
                error = E_DEVICE_DATA_RETURN_ERROR;
        }
        return error;
    }
    return E_THREAD_NO_HANDLE;
}

HE_CONTROLLER_END_NAMESPACE

