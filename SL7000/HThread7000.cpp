#include "HThread7000_p.h"
#include "HKeyenceStrategy.h"
#include "HeCore/HCore.h"
#include "HeData/ITestData.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeController/IControllerFactory.h"
#include <QtCore/QDebug>

HThread7000Private::HThread7000Private()
{
    auto protocolCollection = HAppContext::getContextPointer<IProtocolCollection>("IProtocolCollection");
    protocolKeyence = protocolCollection->value("Keyence");
    protocols << protocolKeyence;
}

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
    d->strategyKeyence = new HKeyenceStrategy(this);
    d->strategyKeyence->setProtocol(d->protocolKeyence);
    d->strategys.prepend(d->strategyKeyence);
}

bool HThread7000::handleAction(HActionType action)
{
    Q_D(HThread7000);
    qDebug() << action << "\t" << HCore::toComment(action);
    if (action == ACT_SET_MOTOR_LOCATION)
        qDebug() << d->testData->data("[电机定位]");
    return HIntegrateThread::handleAction(action);
}
