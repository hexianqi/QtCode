#include "HBuilder2000_p.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/IDevice.h"
#include "HeCommunicate/IDeviceCollection.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeCommunicate/HCommunicateFactory.h"
#include "HeController/IThreadCollection.h"
#include "HeController/HControllerFactory.h"
#include "HeController/HTestDataFactory.h"
#include "HeController/HThreadSpec.h"
#include "HeGui/HMainWindow.h"


#include "HeController/HAbstractModel.h"

HBuilder2000::HBuilder2000(QObject *parent)
    : HAbstractBuilder(*new HAbstractBuilderPrivate, parent)
{
    HAppContext::setContextValue("Settings", "Ini\\SL2000.ini");
}

HBuilder2000::~HBuilder2000()
{
}

HMainWindow *HBuilder2000::createMainWindow()
{
    auto mainWindow = new HMainWindow;
    buildFactory();
    buildTestData();
    buildDevices();
    buildProtocols();
    buildThreads();
    buildModel();
    return mainWindow;
}

void HBuilder2000::buildFactory()
{
    Q_D(HBuilder2000);
    d->communicateFactory = new HCommunicateFactory;
    d->controllerFactory = new HControllerFactory;
    d->testDataFactory = new HTestDataFactory;
    HAppContext::setContextPointer("ICommunicateFactory", d->communicateFactory);
    HAppContext::setContextPointer("IControllerFactory", d->controllerFactory);
    HAppContext::setContextPointer("ITestDataFactory", d->testDataFactory);
}

void HBuilder2000::buildTestData()
{
    Q_D(HBuilder2000);
    QVariantMap param1, param2;
    auto other = d->testDataFactory->createTestData("Other");
    param1.insert("successor", ToVariant(other));
    auto spec = d->testDataFactory->createTestSpec("Spec", param1);
    param2.insert("successor", ToVariant(spec));
    auto main = d->testDataFactory->createTestData("Main", param2);
    HAppContext::setContextPointer("ITestOther", other);
    HAppContext::setContextPointer("ITestSpec", spec);
    HAppContext::setContextPointer("ITestMain", main);
}

void HBuilder2000::buildDevices()
{
    Q_D(HBuilder2000);
    QVariantMap param;
    param.insert("timeOut", 1000);
    auto port = d->communicateFactory->createPort("USB_Cy", param);
    auto device = d->communicateFactory->createDevice("SL");
    device->setPort(port, 0, false);
    device->setDeviceID(0x81);
    device->addActionParam(ACT_CHECK_DEVICE,        QList<uchar>() << 0x00 << 0x04 << 0x03 << 0x00);
    device->addActionParam(ACT_SET_INTEGRAL_TIME,   QList<uchar>() << 0x00 << 0x04 << 0x03 << 0x05);
    device->addActionParam(ACT_GET_SPECTRUM,        QList<uchar>() << 0x12 << 0x00 << 0x03 << 0x11);
    d->devices = d->communicateFactory->createDeviceCollection("2000");
    d->devices->insert("Spec", device);
    //    devices->addSupport(ACT_PULSE_TEST);
    //    devices->addSupport(ACT_GET_LUMINOUS_SPECTRUM);
    //    devices->addSupport(ACT_GET_ELEC_LUMINOUS_SPECTRUM);
    HAppContext::setContextPointer("IDeviceCollection", d->devices);
}

void HBuilder2000::buildProtocols()
{
    Q_D(HBuilder2000);
    QVariantMap param;
    param.insert("device", ToVariant(d->devices->value("Spec")));
    auto protocol = d->communicateFactory->createProtocol("Spec", param);
    auto protocols = d->communicateFactory->createProtocolCollection("2000");
    protocols->insert("Spec", protocol);
    HAppContext::setContextPointer("IProtocolCollection", protocols);
}

void HBuilder2000::buildThreads()
{
    Q_D(HBuilder2000);
    auto threads = d->controllerFactory->createThreadCollection("2000");
    threads->insert("Spec", new HThreadSpec);
    HAppContext::setContextPointer("IThreadCollection", threads);
}

void HBuilder2000::buildModel()
{
//    Q_D(HBuilder2000);
//    d->model = new HAbstractModel;
//    HAppContext::setContextPointer("IModel", model);
//    d->model->initConfig();

}

void HBuilder2000::buildMainWindow()
{
//    Q_D(HBuilder2000);
//    d->window->setModel(d->model);

}
