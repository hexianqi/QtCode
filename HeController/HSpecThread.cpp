#include "HSpecThread_p.h"
#include "IControllerFactory.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/IProtocolCollection.h"
#include <QtCore/QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HSpecThreadPrivate::HSpecThreadPrivate()
{
    protocols.insert("Spec", HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection")->value("Spec"));
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

void HSpecThread::init()
{
    Q_D(HSpecThread);
    d->strategys.insert("Spec", HAppContext::getContextPointer<IControllerFactory>("IControllerFactory")->createStrategy("HSpecStrategy", this));
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

HE_CONTROLLER_END_NAMESPACE

