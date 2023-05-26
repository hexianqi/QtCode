#include "HBuilder1000I_p.h"
#include "HTestWidget1000I.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeData/IConfigManage.h"
#include "HeData/IDataFactory.h"
#include "HeData/IDataStream.h"
#include "HeData/ISpecCalibrateCollection.h"
#include "HeData/IElecCalibrate.h"
#include "HeData/IElecCalibrateCollection.h"
#include "HeData/ILuminousCalibrate.h"
#include "HeData/ILuminousCalibrateItem.h"
#include "HeData/ILuminousCalibrateCollection.h"
#include "HeData/ITestSpec.h"
#include "HeCommunicate/ICommunicateFactory.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeController/IControllerFactory.h"
#include "HeController/IThreadCollection.h"
#include "HeController/IMemento.h"
#include "HeController/IMementoCollection.h"
#include "HeGui/IGuiFactory.h"
#include "HeGui/IMainWindow.h"
#include "HeGui/HAction.h"
#include "HeSql/ISqlFactory.h"
#include "HeSql/ISqlDatabase.h"
#include "HeSql/HSql.h"
#include "HeSql/HSqlHelper.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>

HBuilder1000IPrivate::HBuilder1000IPrivate()
{
    deploy.insert("CcdProtocol",    "HCcdProtocol01");      // HCcdProtocol01:1305; HCcdProtocol02:554b
    HAppContext::setContextValue("SpecCalibrateSetWidgetType",  "HSpecCalibrateSetWidget2");
    HAppContext::setContextValue("AdjustSetWidgetType",         "HAdjustSetWidget2");
    HAppContext::setContextValue("AdjustOptional",              QStringList() << "[实测电压]" << "[实测电流]" << "[辐射强度]" << "[辐射通量]" << "[峰值波长]");
    HAppContext::setContextValue("GradeOptional",               QStringList() << "[实测电压]" << "[实测电流]" << "[反向漏流]" << "[电功率]" << "[辐射强度]" << "[辐射通量]" << "[峰值波长]");
    HAppContext::setContextValue("SpecQualityOptional",         QStringList() << "[实测电压]" << "[实测电流]" << "[反向漏流]" << "[电功率]" << "[辐射强度]" << "[辐射通量]" << "[峰值波长]");
    HAppContext::setContextValue("AngleQualityOptional",        HCore::membership("|辐射强度角度信息2|"));
    HAppContext::setContextValue("TrendOptional",               QStringList() << "[实测电压]" << "[实测电流]" << "[电功率]" << "[辐射强度]" << "[辐射通量]"  << "[峰值波长]");
}

HBuilder1000I::HBuilder1000I(QObject *parent) :
    HAbstractBuilder(*new HBuilder1000IPrivate, parent)
{
}

HBuilder1000I::~HBuilder1000I() = default;

QString HBuilder1000I::typeName()
{
    return "HBuilder1000I";
}

void HBuilder1000I::buildConfigManage()
{
    Q_D(HBuilder1000I);
    d->configManage = d->dataFactory->createConfigManage("HConfigManage");
    if (!d->configManage->stream()->readFile(d->configFileName))
    {
        auto specs = d->dataFactory->createSpecCalibrateCollection("HSpecCalibrateCollection");
        if (!specs->dataStream()->readFile(":/dat/Spectrum.hcs"))
            specs->insert("1", d->dataFactory->createSpecCalibrate("HSpecCalibrate"));

        QVariantMap param[6];
        param[0].insert("itemClassName",    "HElecCalibrateItem");
        param[0].insert("itemTypes",        QStringList() << "[输出电压]");
        param[1].insert("itemClassName",    "HElecCalibrateItem");
        param[1].insert("itemTypes",        QStringList() << "[输出电流1]" << "[输出电流2]" << "[输出电流3]");
        param[2].insert("itemClassName",    "HElecCalibrateItem");
        param[2].insert("itemTypes",        QStringList() << "[实测电压]");
        param[3].insert("itemClassName",    "HElecCalibrateItem");
        param[3].insert("itemTypes",        QStringList() << "[实测电流1]" << "[实测电流2]" << "[实测电流3]");
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

        auto luminousC = d->dataFactory->createLuminousCalibrateCollection("HLuminousCalibrateCollection");
        auto luminous = d->dataFactory->createLuminousCalibrate("HLuminousCalibrate");
        auto luminousI1 = d->dataFactory->createLuminousCalibrateItem("HLuminousCalibrateItem");
        auto luminousI2 = d->dataFactory->createLuminousCalibrateItem("HLuminousCalibrateItem");
        luminousI1->setData("[项类型]", "[辐射强度]");
        luminousI2->setData("[项类型]", "[辐射通量]");
        luminous->insert("[辐射强度]", luminousI1);
        luminous->insert("[辐射通量]", luminousI2);
        luminous->setTotalGears(5);
        luminousC->insert("模块1", luminous);

        d->configManage->setContain(IConfigManage::ContainSpec
                                    | IConfigManage::ContainElec
                                    | IConfigManage::ContainLuminous
                                    | IConfigManage::ContainGrade
                                    | IConfigManage::ContainAdjust
                                    | IConfigManage::ContainQuality);
        d->configManage->setSpecCalibrateCollection(specs);
        d->configManage->setElecCalibrateCollection(elecs);
        d->configManage->setLuminousCalibrateCollection(luminousC);
        d->configManage->setGradeCollection(d->dataFactory->createGradeCollection("HGradeCollection"));
        d->configManage->setAdjustCollection(d->dataFactory->createAdjustCollection("HAdjustCollection"));
        d->configManage->addQualityCollection("SpecI",  d->dataFactory->createQualityCollection("HQualityCollection"));
        d->configManage->addQualityCollection("AngleI", d->dataFactory->createQualityCollection("HQualityCollection"));
    }
    HAppContext::setContextPointer("IConfigManage", d->configManage);
}

void HBuilder1000I::buildTestData()
{
    Q_D(HBuilder1000I);
    auto data = d->dataFactory->createTestData("HTestData");
    auto product = d->dataFactory->createTestData("HTestProduct");
    auto elec = d->dataFactory->createTestData("HTestElec");
    auto luminous = d->dataFactory->createTestData("HTestLuminous");
    auto spec = d->dataFactory->createTestSpec("HTestSpec");
    spec->setCalibrate(d->configManage->specCalibrate("1"));
    elec->setCalibrate(d->configManage->elecCalibrateCollection());
    elec->setData("[输出电压]", 10);
    luminous->setCalibrate(d->configManage->luminousCalibrateCollection());
    luminous->setData("[红外测试]", true);
    data->setSuccessor(product)->setSuccessor(luminous)->setSuccessor(elec)->setSuccessor(spec);
    HAppContext::setContextPointer("ITestData", data);
    HAppContext::setContextPointer("ITestProduct", product);
    HAppContext::setContextPointer("ITestLuminous", luminous);
    HAppContext::setContextPointer("ITestElec", elec);
    HAppContext::setContextPointer("ITestSpec", spec);
}

void HBuilder1000I::buildTemplate()
{
    Q_D(HBuilder1000I);
    auto textExport = d->dataFactory->createTextExport("HTextExport");
    auto specTextTemplate = d->guiFactory->createTextExportTemplate("HSpecTextExportTemplate");
//    auto angleTextTemplate = d->guiFactory->createTextExportTemplate("HAngleTextExportTemplate");
    auto print = d->dataFactory->createPrint("HPrint");
//    auto anglePrintTemplate = d->guiFactory->createPrintTemplate("HAnglePrintTemplate");
//    auto specPrintTemplate = new HSpecPrintTemplate1000I(this);
//    specPrintTemplate->initialize();
//    HAppContext::setContextPointer("ITextExport", textExport);
//    HAppContext::setContextPointer("ISpecTextExportTemplate", specTextTemplate);
//    HAppContext::setContextPointer("IAngleTextExportTemplate", angleTextTemplate);
    HAppContext::setContextPointer("IPrint", print);
//    HAppContext::setContextPointer("IAnglePrintTemplate", anglePrintTemplate);
//    HAppContext::setContextPointer("ISpecPrintTemplate", specPrintTemplate);
}

void HBuilder1000I::buildDevice()
{
    Q_D(HBuilder1000I);
#ifdef SIMULATE // 模拟设备
    auto device1 = d->communicateFactory->createDevice("HSpecSimulateDevice");
    auto device2 = d->communicateFactory->createDevice("HSimulateDevice");
    auto convert1 = d->communicateFactory->createUCharConvert("HLittleUCharConvert");
    auto convert2 = d->communicateFactory->createUCharConvert("HLittleUCharConvert");
    auto protocol1 = d->communicateFactory->createProtocol("HProtocol");
    auto protocol2 = d->communicateFactory->createProtocol("HProtocol");
    protocol1->setConvert(convert1);
    protocol1->setDevice(device1);
    protocol2->setConvert(convert2);
    protocol2->setDevice(device2);
#else
    auto protocol1 = d->communicateFactory->createProtocol(deployItem("CcdProtocol"), this);
    auto protocol2 = d->communicateFactory->createProtocol("HSl1000Protocol", this);
#endif
    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
    protocols->insert("Spec", protocol1);
    protocols->insert("Else", protocol2);
    HAppContext::setContextPointer("IProtocolCollection", protocols);
}

void HBuilder1000I::buildThread()
{
    Q_D(HBuilder1000I);
    auto thread = d->controllerFactory->createThread("HIntegrateThread");
    auto threads = d->controllerFactory->createThreadCollection("HThreadCollection");
    threads->insert("1", thread);
    HAppContext::setContextPointer("IThreadCollection", threads);
}

void HBuilder1000I::buildModel()
{
    Q_D(HBuilder1000I);
    auto model = d->controllerFactory->createModel("HIntegrateModel");
    HAppContext::setContextPointer("IModel", model);
}

void HBuilder1000I::buildMemento()
{
    Q_D(HBuilder1000I);
    auto mementos = d->controllerFactory->createMementoCollection("HMementoCollection");
    auto ok = mementos->readFile(QString("%1.tmp").arg(QApplication::applicationName()));
    if (!ok || !mementos->contains("SpecI"))
    {
        auto memento = d->controllerFactory->createMemento("HMemento");
        memento->setDataType(QStringList() << "[积分时间]" << "[输出电流_档位]" << "[实测电流_档位]" << "[输出电压]" << "[输出电流]" << "[反向电压]" << "[光测试类型]" << "[光档位]");
        mementos->insert("SpecI", memento);
    }
    if (!ok || !mementos->contains("AngleI"))
    {
        auto memento = d->controllerFactory->createMemento("HMemento");
        memento->setDataType(QStringList() << "[输出电流_档位]" << "[实测电流_档位]" << "[输出电压]" << "[输出电流]" << "[光档位]");
        mementos->insert("AngleI", memento);
    }
    HAppContext::setContextPointer("IMementoCollection", mementos);
}

void HBuilder1000I::buildDatabase()
{
    Q_D(HBuilder1000I);
    auto db = d->sqlFactory->createDatabase("HSqliteDatabase");
    db->openConnection();

    HSqlHelper::updateSpecITable(db);
    // SpecI
    {
        auto group = QStringList() << "|产品信息2|" << "|环境信息|" << "|时间信息2|" << "|直流电信息|";
        auto field = QStringList() << "ID" << HSql::membership(group) << "[辐射强度]" << "[辐射通量]"  << "[峰值波长]";
        auto model = createSqlTableModel("SpecI", field);
        db->insertTableModel(model);
    }
    // AngleI
    HSqlHelper::updateAngleITable(db);
    {
        auto field = QStringList() << "ID" << HSql::membership("|辐射强度角度信息|");
        auto model = createSqlTableModel("AngleI", field);
        db->insertTableModel(model);
    }
}

void HBuilder1000I::buildMenu()
{
    Q_D(HBuilder1000I);
    QVariantMap param[7];
    param[0].insert("authority",            1);
    param[1].insert("property",             param[0]);
    param[2].insert("key",                  "SpecI");
    param[2].insert("optional",             "SpecQualityOptional");
    param[3].insert("key",                  "AngleI");
    param[3].insert("optional",             "AngleQualityOptional");
    param[4].insert("sqlBrowser",           "ISpecSqlBrowser");
    param[5].insert("sqlBrowser",           "IAngleSqlBrowser");
    param[6].insert("printTemplate",        "ISpecPrintTemplate");
    param[6].insert("printSettingDialog",   "HSpecPrintSettingDialog");
    auto calibrate = new QMenu(tr("定标(&C)"));
    auto grade = new QMenu(tr("分级(&G)"));
    auto adjust = new QMenu(tr("调整(&A)"));
    auto quality = new QMenu(tr("品质(&Q)"));
    auto device = new QMenu(tr("设备配置(&T)"));
    auto test = new QMenu(tr("其他测试(&E)"));
    auto database = new QMenu(tr("数据库(&D)"));
    auto account = new QMenu(tr("账号管理(&M)"));
    calibrate->menuAction()->setProperty("authority", 1);
    grade->menuAction()->setProperty("authority", 1);
    device->menuAction()->setProperty("authority", 1);
    calibrate->addAction(d->guiFactory->createAction(tr("光谱定标(&S)..."), "HSpecCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("电定标(&E)..."), "HElecCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("光定标(&E)..."), "HLuminousCalibrateHandler"));
    grade->addAction(d->guiFactory->createAction(tr("分级数据配置(&E)..."), "HGradeEditHandler"));
    grade->addAction(d->guiFactory->createAction(tr("分级数据选择(&S)..."), "HGradeSelectHandler"));
    adjust->addAction(d->guiFactory->createAction(tr("调整数据配置(&E)..."), "HAdjustEditHandler", param[1]));
    adjust->addAction(d->guiFactory->createAction(tr("调整数据选择(&S)..."), "HAdjustSelectHandler"));
    quality->addAction(d->guiFactory->createAction(tr("光谱品质数据配置(&E)..."), "HQualityEditHandler", param[2]));
    quality->addAction(d->guiFactory->createAction(tr("光谱品质数据选择(&S)..."), "HQualitySelectHandler", param[2]));
    quality->addAction(d->guiFactory->createAction(tr("辐射强度角品质数据配置(&E)..."), "HQualityEditHandler", param[3]));
    quality->addAction(d->guiFactory->createAction(tr("辐射强度角品质数据选择(&S)..."), "HQualitySelectHandler", param[3]));
    device->addAction(d->guiFactory->createAction(tr("从设备读取数据(&G)..."), "HImportDeviceHandler"));
    device->addAction(d->guiFactory->createAction(tr("写入数据到设备(&S)..."), "HExportDeviceHandler"));
    device->addAction(d->guiFactory->createAction(tr("导入标准曲线(&I)..."), "HImportCurveHandler"));
    device->addAction(d->guiFactory->createAction(tr("导出标准曲线(&E)..."), "HExportCurveHandler"));
//    test->addAction(d->guiFactory->createAction(tr("辐射强度角度测试(&A)..."), "HAngleITestHandler"));
    test->addAction(d->guiFactory->createAction(tr("老化测试(&I)..."), "HTrendTestHandler"));
    test->addAction(d->guiFactory->createAction(tr("IV测试(&I)..."), "HIVTestHandler"));
//    database->addAction(d->guiFactory->createAction(tr("光谱产品信息配置(&E)..."), "HProductEditHandler"));
//    database->addAction(d->guiFactory->createAction(tr("光谱数据打印配置(&P)..."), "HPrintSettingHandler", param[6]));
//    database->addAction(d->guiFactory->createAction(tr("光谱数据库浏览(&S)..."), "HSqlBrowserHandler", param[4]));
//    database->addAction(d->guiFactory->createAction(tr("辐射强度角数据库浏览(&A)..."), "HSqlBrowserHandler", param[5]));
    account->addAction(d->guiFactory->createAction(tr("管理员登入(&I)..."), "HLoginInHandler"));
    account->addAction(d->guiFactory->createAction(tr("注销(&O)..."), "HLoginOutHandler"));
    d->mainWindow->insertMenu(calibrate);
    d->mainWindow->insertMenu(grade);
    d->mainWindow->insertMenu(adjust);
    d->mainWindow->insertMenu(quality);
    d->mainWindow->insertMenu(device);
    d->mainWindow->insertMenu(test);
    d->mainWindow->insertMenu(database);
    d->mainWindow->insertMenu(account);
#ifndef QT_DEBUG
    d->mainWindow->setAuthority(0);
#endif
}

void HBuilder1000I::buildTestWidget()
{
    ITestWidget *widget = new HTestWidget1000I;
    HAppContext::setContextPointer("ITestWidget", widget);
}
