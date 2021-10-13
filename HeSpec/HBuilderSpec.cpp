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
#include "HeGui/IGuiFactory.h"
#include "HeGui/IMainWindow.h"
#include "HeGui/HAction.h"
#include "HeGui/HSpecCalibrateWidget.h"
#include "HeGui/HSpecCalibrateSetWidget.h"
#include <QtWidgets/QMenu>
#include <QtCore/QDebug>

HBuilderSpecPrivate::HBuilderSpecPrivate()
{
    deploy.insert("SpecFitting",    "HSpecFittingPolynom"); // HSpecFittingPolynom: 多项式拟合; HSpecFittingLinear : 插值拟合
    deploy.insert("CcdProtocol",    "HCcdProtocol01");      // HCcdProtocol01:1305; HCcdProtocol02:554b
}

HBuilderSpec::HBuilderSpec(QObject *parent) :
    HAbstractBuilder(*new HBuilderSpecPrivate, parent)
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
    spec->setCalibrate(d->configManage->specCalibrate("1"));
    data->setSuccessor(spec)->setSuccessor(other);
    HAppContext::setContextPointer("ITestData", data);
    HAppContext::setContextPointer("ITestOther", other);
    HAppContext::setContextPointer("ITestSpec", spec);
}

void HBuilderSpec::buildDevice()
{
    Q_D(HBuilderSpec);
#ifdef SIMULATE // 模拟设备
     auto device = d->communicateFactory->createDevice("HSpecSimulateDevice");
     auto protocol = d->communicateFactory->createProtocol("HLittleProtocol");
     protocol->setDevice(device);
#else
    auto protocol = d->communicateFactory->createProtocol(deployItem("CcdProtocol"));
#endif
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

void HBuilderSpec::buildMemento()
{
}

void HBuilderSpec::buildDatabase()
{
}

void HBuilderSpec::buildMenu()
{
    Q_D(HBuilderSpec);
    auto device = new QMenu(tr("设备配置(&T)"));
    device->addAction(d->guiFactory->createAction(tr("导入设备数据(&G)..."), "HImportDeviceHandler"));
    device->addAction(d->guiFactory->createAction(tr("导出设备数据(&S)..."), "HExportDeviceHandler"));
    device->addAction(d->guiFactory->createAction(tr("导入标准曲线(&I)..."), "HImportCurveHandler"));
    device->addAction(d->guiFactory->createAction(tr("导出标准曲线(&E)..."), "HExportCurveHandler"));
    d->mainWindow->insertMenu(device);
}

void HBuilderSpec::buildTestWidget()
{
    Q_D(HBuilderSpec);
    auto widget = new HSpecCalibrateWidget;
    widget->setCalibrate(d->configManage->specCalibrate("1"));
    HAppContext::setContextPointer("ITestWidget", widget);
}
