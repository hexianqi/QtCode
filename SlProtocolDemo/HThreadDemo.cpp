#include "HThreadDemo_p.h"
#include "HProtocolDemo.h"
#include "HTestSpecDemo.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestSpec.h"
#include <QtGui/QPolygonF>
#include <QtCore/QDebug>

HThreadDemoPrivate::HThreadDemoPrivate()
{
    actionSupport << ACT_SET_INTEGRAL_TIME
                  << ACT_GET_SPECTRUM
                  << ACT_GET_SPECTRUM
                  << ACT_GET_SPECTRUM_ENERGY
                  << ACT_SET_DATA;
    protocol = new HProtocolDemo;
    protocols.insert("Spec", protocol);
    testSpec = HAppContext::getContextPointer<HTestSpecDemo>("ITestSpec");
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
    HErrorType error;
    QVector<double> dbuff;
    QPolygonF poly;
    double percent;

    switch(action)
    {
    case ACT_SET_INTEGRAL_TIME:
        return d->protocol->setIntegralTime(d->testSpec->data("[积分时间]").toDouble());
    case ACT_SET_SPECTRUM_AVG_TIMES:
        return d->protocol->setSmooth(d->testSpec->data("[光谱平滑次数]").toInt(), d->testSpec->data("[光谱平滑范围]").toInt());
    case ACT_SET_DATA:
        return d->protocol->setStdCurve(d->testSpec->stdCurve());
    case ACT_GET_SPECTRUM:
        error = d->protocol->getSpectrumSample(dbuff);
        if (error == E_OK)
            d->testSpec->setSample(dbuff, true);
        return error;
    case ACT_GET_SPECTRUM_ENERGY:
        error = d->protocol->getSpectrumEnergy(poly, &percent);
        if (error == E_OK)
            d->testSpec->setEnergy(poly, percent);
        return error;
    }
    return E_THREAD_NO_HANDLE;
}
