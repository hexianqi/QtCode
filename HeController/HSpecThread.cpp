#include "HSpecThread_p.h"
#include "IControllerFactory.h"
#include "IActionStrategy.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/IProtocolCollection.h"

HE_BEGIN_NAMESPACE

HSpecThreadPrivate::HSpecThreadPrivate()
{
    protocols << HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection")->value("Spec");
}

HSpecThread::HSpecThread(QObject *parent) :
    HAbstractThread(*new HSpecThreadPrivate, parent)
{
    init();
}

HSpecThread::HSpecThread(HSpecThreadPrivate &p, QObject *parent) :
    HAbstractThread(p, parent)
{
    init();
}

HSpecThread::~HSpecThread() = default;

QString HSpecThread::typeName()
{
    return "HSpecThread";
}

QString HSpecThread::threadInfo()
{
    return tr("线程");
}

void HSpecThread::init()
{
    Q_D(HSpecThread);
    auto factory = HAppContext::getContextPointer<IControllerFactory>("IControllerFactory");
    auto strategy = factory->createStrategy("HSpecStrategy", this);
    strategy->setProtocol(d->protocols.first());
    d->strategys << strategy;
}

HE_END_NAMESPACE
