#include "HBuilderSpec_p.h"
#include "HModelSpec.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/ICommunicateFactory.h"
#include "HeCommunicate/IDevice.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeController/IControllerFactory.h"
#include "HeController/IThreadCollection.h"
#include "HeData/IConfigManage.h"
#include "HeData/IDataFactory.h"
#include "HeData/IDataStream.h"
#include "HeData/ITestSpec.h"
#include "HeData/ISpecCalibrateCollection.h"
#include "HeData/ISpecCalibrate.h"
#include "HeGui/HSpecCalibrateWidget.h"
#include "HeGui/HSpecCalibrateSetWidget.h"
#include <QtCore/QDebug>

HBuilderSpecPrivate::HBuilderSpecPrivate(IMainWindow *p) :
    HAbstractBuilderPrivate(p)
{
    deploy.insert("SpecFitting",    "HSpecFittingPolynom"); // HSpecFittingPolynom: 多项式拟合; HSpecFittingLinear : 插值拟合
    deploy.insert("Protocol",       "HCcdProtocol01");      // HCcdProtocol01:1305; HCcdProtocol02:554b
}

HBuilderSpec::HBuilderSpec(IMainWindow *parent) :
    HAbstractBuilder(*new HBuilderSpecPrivate(parent), parent)
{
}

HBuilderSpec::~HBuilderSpec()
{
    qDebug() << __func__;
}

void HBuilderSpec::initialize(QVariantMap /*param*/)
{
}

QString HBuilderSpec::typeName()
{
    return "HBuilderSpec";
}

void HBuilderSpec::buildConfigManage()
{
    Q_D(HBuilderSpec);
    d->configManage = d->dataFactory->createConfigManage("HConfigManage");
    if (!d->configManage->stream()->readFile(d->configFileName))
    {
        auto specs = d->dataFactory->createSpecCalibrateCollection("HSpecCalibrateCollection");
        if (!specs->dataStream()->readFile(":/dat/Spectrum.hcs"))
        {
            auto fit = d->dataFactory->createSpecFitting(deployItem("SpecFitting"));
            auto spec = d->dataFactory->createSpecCalibrate("HSpecCalibrate");
            spec->setFitting(fit);
            specs->insert("1", spec);
        }
        d->configManage->setContain(IConfigManage::ContainSpec);
        d->configManage->setSpecCalibrateCollection(specs);
    }
    HAppContext::setContextPointer("IConfigManage", d->configManage);
}

void HBuilderSpec::buildTestData()
{
    Q_D(HBuilderSpec);
    auto data = d->dataFactory->createTestData("HTestData");
    auto other = d->dataFactory->createTestData("HTestData");
    auto spec = d->dataFactory->createTestSpec("HTestSpec");
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
//    // 设备模拟
//    // auto device = d->communicateFactory->createDevice("HSlSimulation");
//    // auto protocol = d->communicateFactory->createProtocol("HLittleProtocol");
//    // protocol->setDevice(device);
//    // 第一版设备554b
//    auto protocol = d->communicateFactory->createProtocol("HCcd1305Protocol");
//    // 第二版设备1305
//    // auto protocol = d->communicateFactory->createProtocol("HCcd554bProtocol");
    auto protocol = d->communicateFactory->createProtocol(deployItem("Protocol"));
    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
    protocols->insert("Spec", protocol);
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
    d->model = new HModelSpec(this);
    HAppContext::setContextPointer("IModel", d->model);
}

void HBuilderSpec::buildDatabase()
{
}

void HBuilderSpec::buildMenu()
{
}

void HBuilderSpec::buildTestWidget()
{
    Q_D(HBuilderSpec);
    auto widget = new HSpecCalibrateWidget;
    widget->setCalibrate(d->configManage->specCalibrate("1"));
    HAppContext::setContextPointer("ITestWidget", widget);
}
