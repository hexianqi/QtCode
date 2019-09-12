#include "HBuilderDemo_p.h"
#include "HThreadDemo.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/ICommunicateFactory.h"
#include "HeController/IControllerFactory.h"
#include "HeController/IThreadCollection.h"
#include "HeData/IDataFactory.h"
#include "HeData/IConfigManage.h"
#include "HeData/IFileStream.h"
#include "HeData/ISpecCalibrate.h"
#include "HeData/ISpecCalibrateCollection.h"
#include "HeData/ITestSpec.h"
#include <QtCore/QDebug>

HBuilderDemo::HBuilderDemo(IMainWindow *parent) :
    HAbstractBuilder(*new HBuilderDemoPrivate(parent), parent)
{
}

HBuilderDemo::~HBuilderDemo()
{
    qDebug() << __func__;
}

QString HBuilderDemo::typeName()
{
    return "HBuilderDemo";
}

void HBuilderDemo::buildConfigManage()
{
    Q_D(HBuilderDemo);
    d->configManage = d->dataFactory->createConfigManage("HConfigManage");
    if (!d->configManage->fileStream()->readFile(d->configFileName))
    {
        auto specs = d->dataFactory->createSpecCalibrateCollection("HSpecCalibrateCollection");
        if (!specs->fileStream()->readFile(":/Dat/Spectrum.hcs"))
        {
            auto spec = d->dataFactory->createSpecCalibrate("HSpecCalibrate");
            specs->insert("1", spec);
        }
        d->configManage->setContain(IConfigManage::ContainSpec);
        d->configManage->setSpecCalibrateCollection(specs);
    }
    HAppContext::setContextPointer("IConfigManage", d->configManage);
}

void HBuilderDemo::buildTestData()
{
    Q_D(HBuilderDemo);
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

void HBuilderDemo::buildDevice()
{
}

void HBuilderDemo::buildThread()
{
    Q_D(HBuilderDemo);
    auto thread = new HThreadDemo;
    auto threads = d->controllerFactory->createThreadCollection("HThreadCollection");
    threads->insert("Spec", thread);
    HAppContext::setContextPointer("IThreadCollection", threads);
}

//void HBuilderDemo::buildModel()
//{
//    Q_D(HBuilderDemo);
//    d->model = d->controllerFactory->createModel("HSpecModel");
//    HAppContext::setContextPointer("IModel", d->model);
//}

void HBuilderDemo::buildDatabase()
{
}

void HBuilderDemo::buildMenu()
{
}

//void HBuilderDemo::buildTestWidget()
//{
//    Q_D(HBuilderDemo);
//    auto widget = new HSpecCalibrateWidget;
//    widget->setTestSetWidget(new HSpecCalibrateSetWidget);
//    widget->setSpecCalibrate(d->configManage->specCalibrate("1"));
//    HAppContext::setContextPointer("ITestWidget", widget);
//}


