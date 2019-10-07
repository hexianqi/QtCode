#include "HBuilderDemo_p.h"
#include "HThreadDemo.h"
#include "HModelDemo.h"
#include "HTestWidgetDemo.h"
#include "HTestSpecDemo.h"
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

void HBuilderDemo::initialize(QVariantMap /*param*/)
{

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
            auto fit = d->dataFactory->createSpecFitting("HSpecFittingLinear");
            auto spec = d->dataFactory->createSpecCalibrate("HSpecCalibrate");
            spec->setFitting(fit);
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
    auto spec = new HTestSpecDemo;
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
    auto thread = new HThreadDemo(this);
    auto threads = d->controllerFactory->createThreadCollection("HThreadCollection");
    threads->insert("Spec", thread);
    HAppContext::setContextPointer("IThreadCollection", threads);
}

void HBuilderDemo::buildModel()
{
    Q_D(HBuilderDemo);
    d->model = new HModelDemo(this);
    HAppContext::setContextPointer("IModel", d->model);
}

void HBuilderDemo::buildDatabase()
{
}

void HBuilderDemo::buildMenu()
{
}

void HBuilderDemo::buildTestWidget()
{
    Q_D(HBuilderDemo);
    auto widget = new HTestWidgetDemo;
    widget->setSpecCalibrate(d->configManage->specCalibrate("1"));
    HAppContext::setContextPointer("ITestWidget", widget);
}
