#include "HBuilder1000RGB_p.h"
#include "HProtocol1000RGB.h"
#include "HTestData1000RGB.h"
#include "HThread1000RGB.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeData/IConfigManage.h"
#include "HeData/IDataFactory.h"
#include "HeData/IDataStream.h"
#include "HeData/ISpecCalibrate.h"
#include "HeData/ISpecCalibrateCollection.h"
#include "HeData/IElecCalibrate.h"
#include "HeData/IElecCalibrateCollection.h"
#include "HeData/ILuminousCalibrate.h"
#include "HeData/ILuminousCalibrateItem.h"
#include "HeData/ILuminousCalibrateCollection.h"
#include "HeData/ITestSpec.h"
#include "HeCommunicate/ICommunicateFactory.h"
#include "HeCommunicate/IDevice.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeController/IControllerFactory.h"
#include "HeController/IThreadCollection.h"

HBuilder1000RGBPrivate::HBuilder1000RGBPrivate()
{
    deploy.insert("SpecFitting",    "HSpecFittingPolynom"); // HSpecFittingPolynom: 多项式拟合; HSpecFittingLinear : 插值拟合
    deploy.insert("CcdProtocol",    "HCcdProtocol01");      // HCcdProtocol01:1305; HCcdProtocol02:554b
    HAppContext::setContextValue("SpecCalibrateSetWidgetType",  "HSpecCalibrateSetWidget2");
//    HAppContext::setContextValue("AdjustSetWidgetType",         "HAdjustSetWidget2");
//    HAppContext::setContextValue("AdjustOptional",              QStringList() << "[实测电压]" << "[实测电流]" << "[光强度]" << "[光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[显色指数R9]" << "[色坐标x]" << "[色坐标y]");
//    HAppContext::setContextValue("GradeOptional",               QStringList() << "[实测电压]" << "[实测电流]" << "[反向漏流]" << "[电功率]" << "[光强度]" << "[光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标]");
//    HAppContext::setContextValue("SpecQualityOptional",         QStringList() << "[实测电压]" << "[实测电流]" << "[反向漏流]" << "[电功率]" << "[光强度]" << "[光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标x]" << "[色坐标y]");
//    HAppContext::setContextValue("AngleQualityOptional",        HCore::membership("|光强角度信息2|"));
//    HAppContext::setContextValue("TrendOptional",               QStringList() << "[实测电压]" << "[实测电流]" << "[电功率]" << "[光强度]" << "[光通量]"  << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[色坐标x]" << "[色坐标y]" << "[显色指数Ra]" << "[显色指数R9]");
}

HBuilder1000RGB::HBuilder1000RGB(QObject *parent) :
    HAbstractBuilder(*new HBuilder1000RGBPrivate, parent)
{
}

HBuilder1000RGB::~HBuilder1000RGB() = default;

QString HBuilder1000RGB::typeName()
{
    return "HBuilder1000RGB";
}

void HBuilder1000RGB::buildConfigManage()
{
    Q_D(HBuilder1000RGB);
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

        auto list1 = QStringList() << "共阴" << "共阳";
        auto list2 = QStringList() << "R" << "G" << "B" << "W";
        QStringList currentOutput, currentMeasured;
        for (auto s1 : list1)
        {
            for (auto s2 : list2)
            {
                for (int i = 1; i <= 2; i++)
                {
                    currentOutput << QString("[输出电流-%1%2%3]").arg(s1, s2, QString::number(i));
                    currentMeasured << QString("[实测电流-%1%2%3]").arg(s1, s2, QString::number(i));
                }
            }
        }

        QVariantMap param[6];
        param[0].insert("itemClassName",    "HElecCalibrateItem");
        param[0].insert("itemTypes",        QStringList() << "[输出电压]");
        param[1].insert("itemClassName",    "HElecCalibrateItem");
        param[1].insert("itemTypes",        currentOutput);
        param[2].insert("itemClassName",    "HElecCalibrateItem");
        param[2].insert("itemTypes",        QStringList() << "[实测电压]");
        param[3].insert("itemClassName",    "HElecCalibrateItem");
        param[3].insert("itemTypes",        currentMeasured);
        param[4].insert("itemClassName",    "HElecCalibrateItem");
        param[4].insert("itemTypes",        QStringList() << "[反向电压]");
        param[5].insert("itemClassName",    "HElecCalibrateItem");
        param[5].insert("itemTypes",        QStringList() << "[反向漏流]");
        auto elec = d->dataFactory->createElecCalibrate("HElecCalibrate");
        auto elecs = d->dataFactory->createElecCalibrateCollection("HElecCalibrateCollection");
        elec->setItemCollection(OutputVoltage,   d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[0]));
        elec->setItemCollection(OutputCurrent,   d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[1]));
        elec->setItemCollection(MeasuredVoltage, d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[2]));
        elec->setItemCollection(MeasuredCurrent, d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[3]));
        elec->setItemCollection(ReverseVoltage,  d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[4]));
        elec->setItemCollection(ReverseCurrent,  d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[5]));
        elecs->insert("模块1", elec);

        auto luminousItem = d->dataFactory->createLuminousCalibrateItem("HLuminousCalibrateItem");
        auto luminous = d->dataFactory->createLuminousCalibrate("HLuminousCalibrate");
        auto luminouss = d->dataFactory->createLuminousCalibrateCollection("HLuminousCalibrateCollection");
        luminousItem->setData("[项类型]", "[光强度]");
        luminous->insert("[光强度]", luminousItem);
        luminous->setTotalGears(5);
        luminouss->insert("模块1", luminous);

//        auto chromatisms = d->dataFactory->createChromatismCollection("HChromatismCollection");
//        chromatisms->dataStream()->readFile(":/dat/Chromatism.hcc");

        d->configManage->setContain(IConfigManage::ContainSpec
                                    | IConfigManage::ContainElec
                                    | IConfigManage::ContainLuminous);
        d->configManage->setSpecCalibrateCollection(specs);
        d->configManage->setElecCalibrateCollection(elecs);
        d->configManage->setLuminousCalibrateCollection(luminouss);
//        d->configManage->setChromatismCollection(chromatisms);
//        d->configManage->setGradeCollection(d->dataFactory->createGradeCollection("HGradeCollection"));
//        d->configManage->setAdjustCollection(d->dataFactory->createAdjustCollection("HAdjustCollection"));
//        d->configManage->addQualityCollection("Spec",   d->dataFactory->createQualityCollection("HQualityCollection"));
//        d->configManage->addQualityCollection("Angle",  d->dataFactory->createQualityCollection("HQualityCollection"));
    }
        HAppContext::setContextPointer("IConfigManage", d->configManage);
}

void HBuilder1000RGB::buildTestData()
{
    Q_D(HBuilder1000RGB);
    auto data = d->dataFactory->createTestData("HTestData");
    auto product = d->dataFactory->createTestData("HTestProduct");
    auto elec = new HTestData1000RGB();
    auto luminous = d->dataFactory->createTestData("HTestLuminous");
    auto spec = d->dataFactory->createTestSpec("HTestSpec");
    spec->setCalibrate(d->configManage->specCalibrate("1"));
    elec->setCalibrate(d->configManage->elecCalibrateCollection());
    elec->setData("[输出电压]", 10);
    luminous->setCalibrate(d->configManage->luminousCalibrateCollection());
    data->setSuccessor(product)->setSuccessor(luminous)->setSuccessor(elec)->setSuccessor(spec);
    HAppContext::setContextPointer("ITestData", data);
    HAppContext::setContextPointer("ITestProduct", product);
    HAppContext::setContextPointer("ITestLuminous", luminous);
    HAppContext::setContextPointer("ITestElec", elec);
    HAppContext::setContextPointer("ITestSpec", spec);
}

void HBuilder1000RGB::buildTemplate()
{

}

void HBuilder1000RGB::buildDevice()
{
    Q_D(HBuilder1000RGB);
#ifdef SIMULATE // 模拟设备
    auto device1 = d->communicateFactory->createDevice("HSpecSimulateDevice");
    auto device2 = d->communicateFactory->createDevice("HSimulateDevice");
    auto protocol1 = d->communicateFactory->createProtocol("HLittleProtocol");
    auto protocol2 = d->communicateFactory->createProtocol("HLittleProtocol");
    device2->addActionParam(ACT_GET_ELEC_DATA, QList<uchar>() << 0x00 << 0x18 << 0x01 << 0x11);
    protocol1->setDevice(device1);
    protocol2->setDevice(device2);
#else
    auto protocol1 = d->communicateFactory->createProtocol(deployItem("CcdProtocol"));
    auto protocol2 = new HProtocol1000RGB;
#endif
    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
    protocols->insert("Spec", protocol1);
    protocols->insert("Else", protocol2);
    HAppContext::setContextPointer("IProtocolCollection", protocols);
}

void HBuilder1000RGB::buildThread()
{
    Q_D(HBuilder1000RGB);
    auto thread = new HThread1000RGB(this);
    auto threads = d->controllerFactory->createThreadCollection("HThreadCollection");
    threads->insert("1", thread);
    HAppContext::setContextPointer("IThreadCollection", threads);
}

void HBuilder1000RGB::buildModel()
{

}

void HBuilder1000RGB::buildMemento()
{

}

void HBuilder1000RGB::buildDatabase()
{

}

void HBuilder1000RGB::buildMenu()
{

}

void HBuilder1000RGB::buildTestWidget()
{

}
