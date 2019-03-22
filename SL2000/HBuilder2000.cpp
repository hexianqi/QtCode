#include "HBuilder2000_p.h"
#include "HModel2000.h"
#include "HMainWindow2000.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/IDevice.h"
#include "HeCommunicate/IDeviceCollection.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeCommunicate/HCommunicateFactory.h"
#include "HeData/IConfigManage.h"
#include "HeData/IFileStream.h"
#include "HeData/ISpecCalibrateCollection.h"
#include "HeData/HDataFactory.h"
#include "HeController/ITestSpec.h"
#include "HeController/IThreadCollection.h"
#include "HeController/HControllerFactory.h"
#include "HeGui/HGuiFactory.h"
////#include "HeGui/HAction.h"
#include <QMessageBox>
////#include <QMenuBar>
#include <QDebug>

HBuilder2000::HBuilder2000(QObject *parent)
    : HAbstractBuilder(*new HAbstractBuilderPrivate, parent)
{
    HAppContext::setContextValue("Settings", "Ini\\SL2000.ini");
}

HBuilder2000::~HBuilder2000()
{
    qDebug() << __func__;
}

QWidget *HBuilder2000::createWidget()
{
    Q_D(HBuilder2000);
    buildFactory();
    buildConfigManage();
    buildTestData();
    buildDevice();
    buildThread();
    buildModel();
    buildMainWindow();
    buildMenu();
 //   initMainWindow();
    return d->window;
}

void HBuilder2000::buildFactory()
{
    Q_D(HBuilder2000);
    d->communicateFactory = new HCommunicateFactory(this);
    d->controllerFactory = new HControllerFactory(this);
    d->dataFactory = new HDataFactory(this);
    d->guiFactory = new HGuiFactory(this);
    HAppContext::setContextPointer("ICommunicateFactory", d->communicateFactory);
    HAppContext::setContextPointer("IControllerFactory", d->controllerFactory);
    HAppContext::setContextPointer("IDataFactory", d->dataFactory);
    HAppContext::setContextPointer("IGuiFactory", d->guiFactory);
}

void HBuilder2000::buildConfigManage()
{
    Q_D(HBuilder2000);
    d->configManage = d->dataFactory->createConfigManage("HConfigManage");
    HAppContext::setContextPointer("IConfigManage", d->configManage);
}

void HBuilder2000::buildTestData()
{
    Q_D(HBuilder2000);
    auto data = d->controllerFactory->createTestData("Data");
    auto other = d->controllerFactory->createTestData("Other");
    d->testSpec = d->controllerFactory->createTestSpec("Spec");
    d->testSpec->setSuccessor(other);
    data->setSuccessor(d->testSpec);
    HAppContext::setContextPointer("ITestData", data);
    HAppContext::setContextPointer("ITestOther", other);
    HAppContext::setContextPointer("ITestSpec", d->testSpec);
}

void HBuilder2000::buildDevice()
{
    Q_D(HBuilder2000);
    QVariantMap param;
    param.insert("timeOut", 1000);
    auto port = d->communicateFactory->createPort("HUsbPortCy", param);
    auto device = d->communicateFactory->createDevice("HDeviceSL");
    auto devices = d->communicateFactory->createDeviceCollection("HDeviceCollection");
    auto protocol = d->communicateFactory->createProtocol("HProtocol");
    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
    device->setPort(port, 0, false);
    device->setDeviceID(0x81);
    device->addActionParam(ACT_CHECK_DEVICE,        QList<uchar>() << 0x00 << 0x04 << 0x03 << 0x00);
    device->addActionParam(ACT_SET_INTEGRAL_TIME,   QList<uchar>() << 0x00 << 0x04 << 0x03 << 0x05);
    device->addActionParam(ACT_GET_SPECTRUM,        QList<uchar>() << 0x12 << 0x00 << 0x03 << 0x11);
    devices->insert("Spec", device);
//    devices->addSupport(ACT_PULSE_TEST);
//    devices->addSupport(ACT_GET_LUMINOUS_SPECTRUM);
//    devices->addSupport(ACT_GET_ELEC_LUMINOUS_SPECTRUM);
    protocol->setDevice(device);
    protocols->insert("Spec", protocol);
    HAppContext::setContextPointer("IDeviceCollection", devices);
    HAppContext::setContextPointer("IProtocolCollection", protocols);
}

void HBuilder2000::buildThread()
{
    Q_D(HBuilder2000);
    auto thread = d->controllerFactory->createThread("HThreadSpec");
    auto threads = d->controllerFactory->createThreadCollection("HThreadCollection");
    threads->insert("Spec", thread);
    HAppContext::setContextPointer("IThreadCollection", threads);
}

void HBuilder2000::buildModel()
{
    Q_D(HBuilder2000);
    d->model = new HModel2000(this);
    HAppContext::setContextPointer("IModel", d->model);
}

void HBuilder2000::buildMainWindow()
{
    Q_D(HBuilder2000);
    d->window = new HMainWindow2000;
    connect(d->window, &HAbstractMainWindow::configManageChanged, this, &HBuilder2000::syncData);
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
    QString fileName = "SL2000.cfg";

    if (!d->configManage->fileStream()->readFile(fileName))
    {
        QMessageBox::warning(nullptr, "", tr("找不到配置文件，正在使用默认的配置。"));
        initConfigManage();
    }
    d->window->setConfigFile(fileName);
    d->window->setConfigManage(d->configManage);
    d->window->setModel(d->model);
    syncData(d->configManage->contain());
}

void HBuilder2000::initConfigManage()
{
    Q_D(HBuilder2000);
    auto specs = d->dataFactory->createSpecCalibrateCollection("HSpecCalibrateCollection");
    if (!specs->fileStream()->readFile(":/Dat/Spectrum.hcs"))
    {
        auto spec = d->dataFactory->createSpecCalibrate("HSpecCalibrate");
        specs->insert("1", spec);
    }
    d->configManage->setContain(ConfigContainType::CCT_Spec);
    d->configManage->setSpecCalibrateCollection(specs);
}

void HBuilder2000::syncData(quint32 type)
{
    Q_D(HBuilder2000);
    if (type & ConfigContainType::CCT_Spec)
    {
        d->testSpec->setCalibrate(d->configManage->specCalibrate("1"));
        d->model->addAction(ACT_RESET_SPECTRUM);
    }
}

//void HBuilder2000::buildProtocol()
//{
//    Q_D(HBuilder2000);
//    QVariantMap param;
//    param.insert("device", ToVariant(d->devices->value("Spec")));
//    auto protocol = d->communicateFactory->createProtocol("HProtocol", param);
//    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
//    protocols->insert("Spec", protocol);
//    HAppContext::setContextPointer("IProtocolCollection", protocols);
//}
