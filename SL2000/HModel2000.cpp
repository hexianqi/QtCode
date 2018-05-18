#include "HModel2000_p.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/IPort.h"
#include "HeCommunicate/IDevice.h"
#include "HeCommunicate/IDeviceCollection.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeCommunicate/ICommunicateFactory.h"
#include "HeController/HThreadSpec.h"

HModel2000Private::HModel2000Private(HModel2000 *q)
    : HAbstractModelPrivate(q)
{
}

void HModel2000Private::init()
{
    Q_Q(HModel2000);
    QVariantMap param;
    auto factory = HAppContext::getContextPointer<ICommunicateFactory>("ICommunicateFactory");
    param.insert("timeOut", 1000);
    auto port = factory->createPort("USB_Cy", param);
    auto device = factory->createDevice("SL");
    device->setPort(port, 0, false);
    device->setDeviceID(0x81);
    device->addActionParam(ACT_CHECK_DEVICE,        QList<uchar>() << 0x00 << 0x04 << 0x03 << 0x00);
    device->addActionParam(ACT_SET_INTEGRAL_TIME,   QList<uchar>() << 0x00 << 0x04 << 0x03 << 0x05);
    device->addActionParam(ACT_GET_SPECTRUM,        QList<uchar>() << 0x12 << 0x00 << 0x03 << 0x11);
    devices = factory->createDeviceCollection("");
    devices->insert("Spec", device);
//    devices->addSupport(ACT_PULSE_TEST);
//    devices->addSupport(ACT_GET_LUMINOUS_SPECTRUM);
//    devices->addSupport(ACT_GET_ELEC_LUMINOUS_SPECTRUM);

    QVariantMap param2;
    param2.insert("device", ToVariant(device));
    auto protocol =  factory->createProtocol("Spec", param2);
    auto protocols = factory->createProtocolCollection("");
    protocols->insert("Spec", protocol);
    HAppContext::setContextPointer("IProtocolCollection", protocols);



//    threads->insert("Spec", new HThreadSpec(q));
}

HModel2000::HModel2000(QObject *parent)
    : HAbstractModel(*new HModel2000Private(this), parent)
{
}

HModel2000::HModel2000(HModel2000Private &p, QObject *parent)
    : HAbstractModel(p, parent)
{
}

HModel2000::~HModel2000()
{
}

bool HModel2000::initConfig()
{
    Q_D(HModel2000);
    d->init();
    return HAbstractModel::initConfig();
}


