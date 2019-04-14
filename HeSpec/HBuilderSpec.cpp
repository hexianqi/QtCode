#include "HBuilderSpec_p.h"
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
#include "HeGui/HSpecCalibrateWidget.h"
#include "HeGui/HSpecCalibrateSetWidget.h"
#include <QDebug>

HBuilderSpec::HBuilderSpec(IMainWindow *parent) :
    HAbstractBuilder(*new HAbstractBuilderPrivate, parent)
{
    Q_D(HBuilderSpec);
    d->configFileName = "HeSpec.cfg";
    HAppContext::setContextValue("Settings", "Ini\\HeSpec.ini");
    HAppContext::setContextValue("ConfigFileName", d->configFileName);
}

HBuilderSpec::~HBuilderSpec()
{
    qDebug() << __func__;
}

QString HBuilderSpec::typeName()
{
    return "HBuilderSpec";
}

void HBuilderSpec::buildConfigManage()
{
    Q_D(HBuilderSpec);
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

void HBuilderSpec::buildTestData()
{
    Q_D(HBuilderSpec);
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

void HBuilderSpec::buildDevice()
{
    Q_D(HBuilderSpec);
    QVariantMap param;
    param.insert("timeOut", 3000);
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

void HBuilderSpec::buildThread()
{
    Q_D(HBuilderSpec);
    auto thread = d->controllerFactory->createThread("HSpecThread");
    auto threads = d->controllerFactory->createThreadCollection("HThreadCollection");
    threads->insert("Spec", thread);
    HAppContext::setContextPointer("IThreadCollection", threads);
}

void HBuilderSpec::buildModel()
{
    Q_D(HBuilderSpec);
    d->model = d->controllerFactory->createModel("HSpecModel");
    HAppContext::setContextPointer("IModel", d->model);
}

void HBuilderSpec::buildTestWidget()
{
    Q_D(HBuilderSpec);
    auto widget = new HSpecCalibrateWidget;
    widget->setTestSetWidget(new HSpecCalibrateSetWidget);
    widget->setSpecCalibrate(d->configManage->specCalibrate("1"));
    HAppContext::setContextPointer("ITestWidget", widget);
}
