#include "HThread7000_p.h"
#include "HKeyenceStrategy.h"
#include "HeCore/HCore.h"
#include "HeData/ITestData.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeController/IControllerFactory.h"
#include <QtCore/QDebug>

HThread7000::HThread7000(QObject *parent) :
    HIntegrateThread(*new HThread7000Private, parent)
{
    init();
}

HThread7000::~HThread7000() = default;

QString HThread7000::typeName()
{
    return "HThread2100DC";
}

void HThread7000::init()
{
    Q_D(HThread7000);
    HIntegrateThread::init();
    auto protocolCollection = HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection");
    auto protocol = protocolCollection->value("Keyence");
    auto strategy = new HKeyenceStrategy(this);
    strategy->setProtocol(protocol);
    d->protocols.prepend(protocol);
    d->strategys.prepend(strategy);
}
