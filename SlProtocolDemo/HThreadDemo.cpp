#include "HThreadDemo_p.h"
#include "HProtocolDemo.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestSpec.h"
#include <QtCore/QDebug>

HThreadDemoPrivate::HThreadDemoPrivate()
{
    actionSupport << ACT_SET_INTEGRAL_TIME
                  << ACT_GET_SPECTRUM;
    protocol = new HProtocolDemo;
    protocols.insert("Spec", protocol);
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HThreadDemo::HThreadDemo(QObject *parent) :
    HAbstractThread(*new HThreadDemoPrivate, parent)
{
}

HThreadDemo::~HThreadDemo()
{
    qDebug() << __func__;
}

QString HThreadDemo::typeName()
{
    return "HThreadDemo";
}

QString HThreadDemo::threadInfo()
{
    return tr("光谱线程");
}

HErrorType HThreadDemo::handleAction(HActionType action)
{
    Q_D(HThreadDemo);
//    HErrorType error;

    switch(action)
    {
    case ACT_SET_INTEGRAL_TIME:
        return d->protocol->setData(action, uint(d->testSpec->data("[积分时间]").toDouble() * 500));
//    case ACT_SET_SPECTRUM_AVG_TIMES:
//        return d->protocol->setData(action, d->testSpec->data("[光谱平均次数]").toInt());
//    case ACT_SET_SPECTRUM_SAMPLE_DELAY:
//        return d->protocol->setData(action, d->testSpec->data("[光谱采样延时]").toInt());
//    case ACT_GET_INTEGRAL_TIME:
//        error = d->protocol->getData(action, i);
//        if (error == E_OK)
//            d->testSpec->setData("[积分时间]", i / 500.0);
//        return error;
//    case ACT_GET_SPECTRUM:
//        error = d->protocol->getData(action, dbuff);//d->testSpec->data("[光谱采样等待时间]").toInt());
//        if (error == E_OK)
//            d->testSpec->setSample(dbuff, true);
//        return error;
//    case ACT_SET_RAM:
//        return d->protocol->setData(action, d->testSpec->getRam());
//    case ACT_GET_RAM:
//        error = d->protocol->getData(action, ubuff);
//        if (error == E_OK)
//        {
//            if (!d->testSpec->setRam(ubuff))
//                error = E_DEVICE_DATA_RETURN_ERROR;
//        }
//        return error;
    }
    return E_THREAD_NO_HANDLE;

}
