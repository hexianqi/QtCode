#include "HBuilder1000RGB_p.h"
#include "HProtocol1000RGB.h"
#include "HTestData1000RGB.h"
#include "HThread1000RGB.h"
#include "HTestWidget1000RGB.h"
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
#include "HeGui/IGuiFactory.h"
#include "HeGui/IMainWindow.h"
#include "HeGui/HAction.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>

HBuilder1000RGBPrivate::HBuilder1000RGBPrivate()
{
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
            specs->insert("1", d->dataFactory->createSpecCalibrate("HSpecCalibrate"));

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
    Q_D(HBuilder1000RGB);
    auto model = d->controllerFactory->createModel("HIntegrateModel");
    HAppContext::setContextPointer("IModel", model);
}

void HBuilder1000RGB::buildMemento()
{

}

void HBuilder1000RGB::buildDatabase()
{

}

void HBuilder1000RGB::buildMenu()
{
    Q_D(HBuilder1000RGB);
//    QVariantMap param[7];
//    param[0].insert("authority",            1);
//    param[1].insert("property",             param[0]);
//    param[2].insert("key",                  "Spec");
//    param[2].insert("optional",             "SpecQualityOptional");
//    param[3].insert("key",                  "Angle");
//    param[3].insert("optional",             "AngleQualityOptional");
//    param[4].insert("sqlBrowser",           "ISpecSqlBrowser");
//    param[5].insert("sqlBrowser",           "IAngleSqlBrowser");
//    param[6].insert("printTemplate",        "ISpecPrintTemplate");
//    param[6].insert("printSettingDialog",   "HSpecPrintSettingDialog");
    auto calibrate = new QMenu(tr("定标(&C)"));
//    auto grade = new QMenu(tr("分级(&G)"));
//    auto adjust = new QMenu(tr("调整(&A)"));
//    auto quality = new QMenu(tr("品质(&Q)"));
    auto device = new QMenu(tr("设备配置(&T)"));
//    auto test = new QMenu(tr("其他测试(&E)"));
//    auto database = new QMenu(tr("数据库(&D)"));
    auto account = new QMenu(tr("账号管理(&M)"));
    calibrate->menuAction()->setProperty("authority", 1);
//    grade->menuAction()->setProperty("authority", 1);
//    device->menuAction()->setProperty("authority", 1);
    calibrate->addAction(d->guiFactory->createAction(tr("光谱定标(&S)..."), "HSpecCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("电定标(&E)..."), "HElecCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("光定标(&E)..."), "HLuminousCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("光通量自吸收配置(&L)..."), "HSpecLuminousHandler"));
//    calibrate->addAction(d->guiFactory->createAction(tr("色温配置(&T)..."), "HSpecTcHandler"));
//    grade->addAction(d->guiFactory->createAction(tr("分级数据配置(&E)..."), "HGradeEditHandler"));
//    grade->addAction(d->guiFactory->createAction(tr("分级数据选择(&S)..."), "HGradeSelectHandler"));
//    adjust->addAction(d->guiFactory->createAction(tr("调整数据配置(&E)..."), "HAdjustEditHandler", param[1]));
//    adjust->addAction(d->guiFactory->createAction(tr("调整数据选择(&S)..."), "HAdjustSelectHandler"));
//    quality->addAction(d->guiFactory->createAction(tr("光谱品质数据配置(&E)..."), "HQualityEditHandler", param[2]));
//    quality->addAction(d->guiFactory->createAction(tr("光谱品质数据选择(&S)..."), "HQualitySelectHandler", param[2]));
//    quality->addAction(d->guiFactory->createAction(tr("光强角品质数据配置(&E)..."), "HQualityEditHandler", param[3]));
//    quality->addAction(d->guiFactory->createAction(tr("光强角品质数据选择(&S)..."), "HQualitySelectHandler", param[3]));
    device->addAction(d->guiFactory->createAction(tr("从设备读取数据(&G)..."), "HImportDeviceHandler"));
    device->addAction(d->guiFactory->createAction(tr("写入数据到设备(&S)..."), "HExportDeviceHandler"));
    device->addAction(d->guiFactory->createAction(tr("导入标准曲线(&I)..."), "HImportCurveHandler"));
    device->addAction(d->guiFactory->createAction(tr("导出标准曲线(&E)..."), "HExportCurveHandler"));
//    test->addAction(d->guiFactory->createAction(tr("光强角度测试(&A)..."), "HAngleTestHandler"));
//    test->addAction(d->guiFactory->createAction(tr("老化测试(&I)..."), "HTrendTestHandler"));
//    test->addAction(d->guiFactory->createAction(tr("IV测试(&I)..."), "HIVTestHandler"));
//    database->addAction(d->guiFactory->createAction(tr("光谱产品信息配置(&E)..."), "HProductEditHandler"));
//    database->addAction(d->guiFactory->createAction(tr("光谱数据打印配置(&P)..."), "HPrintSettingHandler", param[6]));
//    database->addAction(d->guiFactory->createAction(tr("光谱数据库浏览(&S)..."), "HSqlBrowserHandler", param[4]));
//    database->addAction(d->guiFactory->createAction(tr("光强角数据库浏览(&A)..."), "HSqlBrowserHandler", param[5]));
    account->addAction(d->guiFactory->createAction(tr("管理员登入(&I)..."), "HLoginInHandler"));
    account->addAction(d->guiFactory->createAction(tr("注销(&O)..."), "HLoginOutHandler"));
    d->mainWindow->insertMenu(calibrate);
//    d->mainWindow->insertMenu(grade);
//    d->mainWindow->insertMenu(adjust);
//    d->mainWindow->insertMenu(quality);
    d->mainWindow->insertMenu(device);
//   d->mainWindow->insertMenu(test);
//    d->mainWindow->insertMenu(database);
//    d->mainWindow->insertMenu(account);
#ifndef QT_DEBUG
    d->mainWindow->setAuthority(0);
#endif
}

void HBuilder1000RGB::buildTestWidget()
{
    ITestWidget *widget = new HTestWidget1000RGB;
    HAppContext::setContextPointer("ITestWidget", widget);
}
