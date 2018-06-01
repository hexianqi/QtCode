#include "HBuilder2000_p.h"
#include "HModel2000.h"
#include "HMainWindow2000.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/IDevice.h"
#include "HeCommunicate/IDeviceCollection.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeCommunicate/HCommunicateFactory.h"
#include "HeData/IConfigManage.h"
#include "HeData/ISpecCalibrateCollection.h"
#include "HeData/HDataFactory.h"
#include "HeController/ITestSpec.h"
#include "HeController/IThreadCollection.h"
#include "HeController/HControllerFactory.h"
#include "HeController/HTestDataFactory.h"
#include "HeController/HThreadSpec.h"
#include "HeGui/HGuiFactory.h"
#include "HeGui/HAction.h"
#include <QMessageBox>
#include <QMenuBar>
#include <QDebug>

HBuilder2000Private::HBuilder2000Private()
{
}

HBuilder2000::HBuilder2000(QObject *parent)
    : HAbstractBuilder(*new HAbstractBuilderPrivate, parent)
{
    HAppContext::setContextValue("Settings", "Ini\\SL2000.ini");
}

HBuilder2000::~HBuilder2000()
{
    qDebug() << __func__;
}

HMainWindow *HBuilder2000::createMainWindow()
{
    Q_D(HBuilder2000);
    buildFactory();
    buildTestData();
    buildConfigManage();
    buildDevices();
    buildProtocols();
    buildThreads();
    buildModel();
    buildMainWindow();
    buildMenu();
    initMainWindow();
    return d->window;
}

void HBuilder2000::buildFactory()
{
    Q_D(HBuilder2000);
    d->dataFactory = new HDataFactory;
    d->testDataFactory = new HTestDataFactory;
    d->communicateFactory = new HCommunicateFactory;
    d->controllerFactory = new HControllerFactory;
    d->guiFactory = new HGuiFactory(this);
    HAppContext::setContextPointer("IDataFactory", d->dataFactory);
    HAppContext::setContextPointer("ITestDataFactory", d->testDataFactory);
    HAppContext::setContextPointer("ICommunicateFactory", d->communicateFactory);
    HAppContext::setContextPointer("IControllerFactory", d->controllerFactory);
    HAppContext::setContextPointer("IGuiFactory", d->guiFactory);
}

void HBuilder2000::buildTestData()
{
    Q_D(HBuilder2000);
    QVariantMap param1, param2;
    auto other = d->testDataFactory->createTestData("Other");
    param1.insert("successor", ToVariant(other));
    d->testSpec = d->testDataFactory->createTestSpec("Spec", param1);
    param2.insert("successor", ToVariant(d->testSpec));
    auto main = d->testDataFactory->createTestData("Main", param2);
    HAppContext::setContextPointer("ITestOther", other);
    HAppContext::setContextPointer("ITestSpec", d->testSpec);
    HAppContext::setContextPointer("ITestMain", main);
}

void HBuilder2000::buildConfigManage()
{
    Q_D(HBuilder2000);
    d->configManage = d->dataFactory->createConfigManage("HConfigManage");
    HAppContext::setContextPointer("IConfigManage", d->configManage);
}

void HBuilder2000::buildDevices()
{
    Q_D(HBuilder2000);
    QVariantMap param;
    param.insert("timeOut", 1000);
    auto port = d->communicateFactory->createPort("HUsbPortCy", param);
    auto device = d->communicateFactory->createDevice("HDeviceSL");
    device->setPort(port, 0, false);
    device->setDeviceID(0x81);
    device->addActionParam(ACT_CHECK_DEVICE,        QList<uchar>() << 0x00 << 0x04 << 0x03 << 0x00);
    device->addActionParam(ACT_SET_INTEGRAL_TIME,   QList<uchar>() << 0x00 << 0x04 << 0x03 << 0x05);
    device->addActionParam(ACT_GET_SPECTRUM,        QList<uchar>() << 0x12 << 0x00 << 0x03 << 0x11);
    d->devices = d->communicateFactory->createDeviceCollection("HDeviceCollection");
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
    auto protocol = d->communicateFactory->createProtocol("HProtocol", param);
    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
    protocols->insert("Spec", protocol);
    HAppContext::setContextPointer("IProtocolCollection", protocols);
}

void HBuilder2000::buildThreads()
{
    Q_D(HBuilder2000);
    auto threads = d->controllerFactory->createThreadCollection("HThreadCollection");
    threads->insert("Spec", new HThreadSpec);
    HAppContext::setContextPointer("IThreadCollection", threads);
}

void HBuilder2000::buildModel()
{
    Q_D(HBuilder2000);
    d->model = new HModel2000;
    HAppContext::setContextPointer("IModel", d->model);
}

void HBuilder2000::buildMainWindow()
{
    Q_D(HBuilder2000);
    d->window = new HMainWindow2000;
    connect(d->window, &HMainWindow::configManageChanged, this, initTestData);
    HAppContext::setContextPointer("MainWindow", d->window);
}

void HBuilder2000::buildMenu()
{
//    Q_D(HBuilder2000);
//    auto help = d->window->menuBar()->addMenu("帮助(&H)");
//    help->addAction(d->guiFactory->createAction(tr("关于(&A)..."), "HAboutHandler"));
//    help->addAction(d->guiFactory->createAction(tr("测试..."), "HTestHandler"));
}

void HBuilder2000::initMainWindow()
{
    Q_D(HBuilder2000);

    d->window->setConfigFile("SL2000.cfg");
    if (!d->window->setConfigManage(d->configManage))
        initConfigManageDefault();
    d->window->setModel(d->model);



    initTestData(d->configManage->contain());
}

void HBuilder2000::initConfigManageDefault()
{
    Q_D(HBuilder2000);
    auto specs = d->dataFactory->createSpecCalibrateCollection("HSpecCalibrateCollection");
    if (!specs->readFile(":/Dat/Spectrum.hcs"))
    {
        auto spec = d->dataFactory->createSpecCalibrate("HSpecCalibrate");
        specs->insert("1", spec);
    }
    d->configManage->setContain(ConfigContainType::CCT_Spec);
    d->configManage->setSpecCalibrateCollection(specs);
}

void HBuilder2000::initTestData(quint32 type)
{
    Q_D(HBuilder2000);
    if (type & ConfigContainType::CCT_Spec)
    {
        d->testSpec->setCalibrate(d->configManage->specCalibrate("1"));
        d->model->addAction(ACT_RESET_SPECTRUM);
    }
}
