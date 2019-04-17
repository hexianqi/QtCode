#include "HBuilder2000_p.h"
#include "HTestWidget2000.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/ICommunicateFactory.h"
#include "HeCommunicate/IDevice.h"
#include "HeCommunicate/IDeviceCollection.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeController/IControllerFactory.h"
#include "HeController/ITestSpec.h"
#include "HeController/IThreadCollection.h"
#include "HeData/IConfigManage.h"
#include "HeData/IDataFactory.h"
#include "HeData/IFileStream.h"
#include "HeData/ISpecCalibrateCollection.h"
#include "HeSql/ISqlFactory.h"
#include "HeSql/ISqlDatabase.h"
#include "HeSql/ISqlTableModel.h"
#include <QtCore/QDebug>

HBuilder2000::HBuilder2000(HeGui::IMainWindow *parent) :
    HAbstractBuilder(*new HAbstractBuilderPrivate, parent)
{
    Q_D(HBuilder2000);
    d->configFileName = "SL2000.cfg";
    HAppContext::setContextValue("Settings", "Ini\\SL2000.ini");
    HAppContext::setContextValue("ConfigFileName", d->configFileName);
}

HBuilder2000::~HBuilder2000()
{
    qDebug() << __func__;
}

QString HBuilder2000::typeName()
{
    return "HBuilder2000";
}

void HBuilder2000::buildConfigManage()
{
    Q_D(HBuilder2000);
    d->configManage = d->dataFactory->createConfigManage("HConfigManage");
    if (!d->configManage->fileStream()->readFile(d->configFileName))
    {
        auto specs = d->dataFactory->createSpecCalibrateCollection("HSpecCalibrateCollection");
        if (!specs->fileStream()->readFile(":/Dat/Spectrum.hcs"))
        {
            auto spec = d->dataFactory->createSpecCalibrate("HSpecCalibrate");
            specs->insert("1", spec);
        }
        d->configManage->setContain(ConfigContainType::CCT_Spec);
        d->configManage->setSpecCalibrateCollection(specs);
    }
    HAppContext::setContextPointer("IConfigManage", d->configManage);
}

void HBuilder2000::buildTestData()
{
    Q_D(HBuilder2000);
    auto data = d->controllerFactory->createTestData("Data");
    auto other = d->controllerFactory->createTestData("Other");
    auto spec = d->controllerFactory->createTestSpec("Spec");
    spec->setSuccessor(other);
    spec->setCalibrate(d->configManage->specCalibrate("1"));
    data->setSuccessor(spec);
    HAppContext::setContextPointer("ITestData", data);
    HAppContext::setContextPointer("ITestOther", other);
    HAppContext::setContextPointer("ITestSpec", spec);
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
    device->addActionParam(ACT_CHECK_DEVICE,        QList<uchar>() << 0x00 << 0x02 << 0x03 << 0x00);
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
    auto thread = d->controllerFactory->createThread("HSpecThread");
    auto threads = d->controllerFactory->createThreadCollection("HThreadCollection");
    threads->insert("Spec", thread);
    HAppContext::setContextPointer("IThreadCollection", threads);
}

void HBuilder2000::buildModel()
{
    Q_D(HBuilder2000);
    d->model = d->controllerFactory->createModel("HSpecModel");
    HAppContext::setContextPointer("IModel", d->model);
}

void HBuilder2000::buildDatabase()
{
    Q_D(HBuilder2000);
    auto field = QStringList() << tr("ID") << tr("Manufacturer") << tr("ProductName") << tr("ProductModel")  << tr("SampleNumber") << tr("Tester") << tr("TestInstitute")
                               << tr("Temperature") << tr("Humidity") << tr("TestDate") << tr("TestTime")
                               << tr("LuminousFluxSpec") << tr("LuminousPower")
                               << tr("PeakWave") << tr("PeakBandwidth") << tr("DominantWave")
                               << tr("ColorTemperature") << tr("ColorPurity")
                               << tr("CC_x") << tr("CC_y") << tr("CC_up") << tr("CC_vp") << tr("Duv")
                               << tr("RedRatio") << tr("GreenRadio") << tr("BlueRatio")
                               << tr("Ra") << tr("Rx") << tr("EnergyGraph");
    auto db = d->sqlFactory->createDatabase("HSqlDatabase");
    auto model = d->sqlFactory->createTableModel("HSqlTableModel");
    db->openDatabase("SL2000.db");
    db->insertTableModel("Spec", model);
    model->setField(field);
    model->setTable("Spec");
    HAppContext::setContextPointer("ISqlTableModel", model);
}

void HBuilder2000::buildTestWidget()
{
    ITestWidget *widget = new HTestWidget2000;
    HAppContext::setContextPointer("ITestWidget", widget);
}

//void HBuilder2000::buildMenu()
//{
//    Q_D(HBuilder2000);
//    auto help = d->window->menuBar()->addMenu("帮助(&H)");
//    help->addAction(d->guiFactory->createAction(tr("关于(&A)..."), "HAboutHandler"));
//    help->addAction(d->guiFactory->createAction(tr("测试..."), "HTestHandler"));
//}

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
