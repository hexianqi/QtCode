#include "HThreadSpec_p.h"
#include "IModel.h"
#include "ITestSpec.h"
#include "HeCommunicate/HProtocol.h"

HE_CORE_USE_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

void HThreadSpecPrivate::init()
{
    Q_Q(HThreadSpec);
    actionSupport = QList<HActionType>()
            << ACT_SET_INTEGRAL_TIME
            << ACT_SET_MACHINE_AVG_TIMES
            << ACT_SET_SPECTRUM_SAMPLE_DELAY
            << ACT_GET_INTEGRAL_TIME
            << ACT_GET_SPECTRUM;

    protocolSpec = new HProtocol(q);
    testSpec = model->testSpec();
    protocols.insert("[光谱仪]", protocolSpec);
}

HThreadSpec::HThreadSpec(IModel *model, QObject *parent)
    : HAbstractThread(model, parent)
{
    Q_D(HThreadSpec);
    d->init();
}

HThreadSpec::HThreadSpec(HThreadSpecPrivate &p, QObject *parent)
    : HAbstractThread(p, parent)
{
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
    HErrorType error = E_OK;

    auto protocol = d->protocols.value("[光谱仪]");
    switch(action)
    {
    case ACT_SET_INTEGRAL_TIME:
        error = protocol->setData(ACT_SET_INTEGRAL_TIME, uint(d->model->testData("[积分时间]").toDouble() * 500));
                //->setIntegralTime(m_pInterface->testSpectrum()->integralTime());
//        if (error == E_OK)
//            m_pInterface->testSpectrum()->clearQueue();
        break;
//    case ACT_SET_MACHINE_AVG_TIMES:
//        err = m_pProtocolSpec->setData(action, m_pInterface->testSpectrum()->machineAvgTimes());
//        break;
//    case ACT_SET_SPECTRUM_SAMPLE_DELAY:
//        err = m_pProtocolSpec->setData(action, m_pInterface->testSpectrum()->delay());
//        break;
//    case ACT_GET_INTEGRAL_TIME:
//        err = m_pProtocolSpec->getData(action, nSample);
//        CHECKERR(err);
//        m_pInterface->testSpectrum()->setIntegralTime(nSample);
//        break;
//    case ACT_GET_SPECTRUM:
//        if (m_pInterface->isExpired())
//            err = m_pProtocolSpec->getSpectrum(dSamples);
//        else
//            err = m_pProtocolSpec->getSpectrum(dSamples, m_pInterface->testSpectrum()->commWaitTime());
//        CHECKERR(err);
//        m_pInterface->testSpectrum()->setSample(dSamples, true);
//        break;
    default:
        return E_OK;
    }

    return error;


}


