#include "HBuilder2000AC_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IDataFactory.h"
#include "HeData/IDataStream.h"
#include "HeData/ISpecCalibrate.h"
#include "HeData/ISpecCalibrateCollection.h"
#include "HeData/IChromatismCollection.h"
#include "HeData/ITestSpec.h"
#include "HeCommunicate/ICommunicateFactory.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeController/IControllerFactory.h"
#include "HeController/IThreadCollection.h"
#include <QtCore/QDebug>

HBuilder2000ACPrivate::HBuilder2000ACPrivate()
{
    deploy.insert("SpecFitting",    "HSpecFittingPolynom"); // HSpecFittingPolynom: 多项式拟合; HSpecFittingLinear : 插值拟合
    deploy.insert("CcdProtocol",    "HCcdProtocol01");      // HCcdProtocol01:1305; HCcdProtocol02:554b
    deploy.insert("PfProtocol",     "HUi2008Protocol");     // HUi2008Protocol:UI2008; HUi2010Protocol:UI2010

    sqlField = QStringList() << "ID" << "Manufacturer" << "ProductName" << "ProductModel" << "SampleNumber" << "Tester" << "TestInstitute"
                             << "Temperature" << "Humidity" << "TestDate" << "TestTime"
                             << "ACCurrent" << "ACVoltage" << "ACPower" << "ACFactor"
                             << "LuminousFluxSpec" << "LuminousPower" << "LuminousEfficiency"
                             << "PeakWave" << "PeakBandwidth" << "DominantWave"
                             << "ColorTemperature" << "ColorPurity"
                             << "CC_x" << "CC_y" << "CC_up" << "CC_vp" << "Duv"
                             << "RedRatio" << "GreenRadio" << "BlueRatio"
                             << "Ra" << "R9" << "Rx" << "EnergyGraph";
    HAppContext::setContextValue("GradeOptionals",              QStringList() << "[交流电压]" << "[交流电流]" << "[交流电功率]" << "[功率因素]" << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标]");
    HAppContext::setContextValue("QualityOptionals",            QStringList() << "[交流电压]" << "[交流电流]" << "[交流电功率]" << "[功率因素]" << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标x]" << "[色坐标y]");
    HAppContext::setContextValue("AdjustOptionals",             QStringList() << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[显色指数R9]" << "[色坐标x]" << "[色坐标y]");
}

HBuilder2000AC::HBuilder2000AC(QObject *parent) :
    HAbstractBuilder(*new HBuilder2000ACPrivate, parent)
{
}

HBuilder2000AC::~HBuilder2000AC()
{
    qDebug() << __func__;
}

void HBuilder2000AC::initialize(QVariantMap /*param*/)
{
}

QString HBuilder2000AC::typeName()
{
    return "HBuilder2000AC";
}

void HBuilder2000AC::buildConfigManage()
{
    Q_D(HBuilder2000AC);
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

        auto chromatisms = d->dataFactory->createChromatismCollection("HChromatismCollection");
        chromatisms->dataStream()->readFile(":/dat/Chromatism.hcc");

        d->configManage->setContain(IConfigManage::ContainSpec
                                    | IConfigManage::ContainChromatism
                                    | IConfigManage::ContainGrade
                                    | IConfigManage::ContainAdjust
                                    | IConfigManage::ContainQuality);
        d->configManage->setSpecCalibrateCollection(specs);
        d->configManage->setChromatismCollection(chromatisms);
        d->configManage->setGradeCollection(d->dataFactory->createGradeCollection("HGradeCollection"));
        d->configManage->setAdjustCollection(d->dataFactory->createAdjustCollection("HAdjustCollection"));
        d->configManage->setQualityCollection(d->dataFactory->createQualityCollection("HQualityCollection"));
    }
    HAppContext::setContextPointer("IConfigManage", d->configManage);
}

void HBuilder2000AC::buildTestData()
{
    Q_D(HBuilder2000AC);
    auto data = d->dataFactory->createTestData("HTestData");
    auto other = d->dataFactory->createTestData("HTestData");
    auto spec = d->dataFactory->createTestSpec("HTestSpec");

    spec->setSuccessor(other);
    spec->setCalibrate(d->configManage->specCalibrate("1"));
    data->setSuccessor(spec);
    HAppContext::setContextPointer("ITestData", data);
    HAppContext::setContextPointer("ITestSpec", spec);
    HAppContext::setContextPointer("ITestOther", other);
}

void HBuilder2000AC::buildDevice()
{
    Q_D(HBuilder2000AC);
#ifdef SIMULATE // 模拟设备
    auto device1 = d->communicateFactory->createDevice("HSpecSimulateDevice");
    auto device2 = d->communicateFactory->createDevice("HSimulateDevice");
    auto protocol1 = d->communicateFactory->createProtocol("HLittleProtocol");
    auto protocol2 = d->communicateFactory->createProtocol("HLittleProtocol");
    protocol1->setDevice(device1);
    protocol2->setDevice(device2);
#else
    auto protocol1 = d->communicateFactory->createProtocol(deployItem("CcdProtocol"));
    auto protocol2 = d->communicateFactory->createProtocol(deployItem("PfProtocol"));
#endif
    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
    protocols->insert("Spec", protocol1);
    protocols->insert("Else", protocol2);
    HAppContext::setContextPointer("IProtocolCollection", protocols);
}

void HBuilder2000AC::buildThread()
{
//    Q_D(HBuilder2000AC);
//    auto thread = d->controllerFactory->createThread("HIntegrateThread");
//    auto threads = d->controllerFactory->createThreadCollection("HThreadCollection");
//    threads->insert("1", thread);
//    HAppContext::setContextPointer("IThreadCollection", threads);
}
