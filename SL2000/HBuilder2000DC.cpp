#include "HBuilder2000DC_p.h"
#include "HTestWidget2000DC.h"
#include "HSpecPrintTemplate2000DC.h"
#include "HeCore/HAppContext.h"
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
#include "HeData/IChromatismCollection.h"
#include "HeData/ITestSpec.h"
#include "HeCommunicate/ICommunicateFactory.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeController/IControllerFactory.h"
#include "HeController/IThreadCollection.h"
#include "HeController/IMemento.h"
#include "HeController/IMementoCollection.h"
#include "HeSql/ISqlFactory.h"
#include "HeSql/ISqlDatabase.h"
#include "HeSql/HSql.h"
#include "HeSql/HSqlHelper.h"
#include "HeGui/IGuiFactory.h"
#include "HeGui/IMainWindow.h"
#include "HeGui/HAction.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>

HBuilder2000DCPrivate::HBuilder2000DCPrivate()
{
    deploy.insert("CcdProtocol",    "HCcdProtocol01");      // HCcdProtocol01:1305; HCcdProtocol02:554b
//    sqlField = QStringList() << "ID" << "Manufacturer" << "ProductName" << "ProductModel" << "SampleNumber" << "Tester" << "TestInstitute"
//                             << "Temperature" << "Humidity" << "TestDate" << "TestTime"
//                             << "OutputVoltage" << "OutputCurrent" << "MeasuredVoltage" << "MeasuredCurrent" << "ReverseVoltage" << "ReverseCurrent" << "ElecPower"
//                             << "LuminousFlux" << "LuminousPower" << "LuminousEfficiency"
//                             << "PeakWave" << "PeakBandwidth" << "DominantWave"
//                             << "ColorTemperature" << "ColorPurity"
//                             << "CC_x" << "CC_y" << "CC_up" << "CC_vp" << "Duv"
//                             << "RedRatio" << "GreenRadio" << "BlueRatio"
//                             << "Ra" << "R9" << "Rx" << "SDCM"
//                             << "Photon380_780" << "Photon400_700" << "Photon700_800" << "PPF" << "PRF" << "PPFE" << "FluorescenceEfficiency" << "FluorescenceRatio"
//                             << "EnergyGraph" << "ReflectGraph"
//                             << "TM30_Rf" << "TM30_Rg" << "TM30_Rfi"
//                             << "TM30_hj_Rf" << "TM30_hj_Rcs" << "TM30_hj_Rhs"
//                             << "TM30_hj_at" << "TM30_hj_bt" << "TM30_hj_ar" << "TM30_hj_br"
//                             << "TM30_hj_atn" << "TM30_hj_btn" << "TM30_hj_arn" << "TM30_hj_brn";
    HAppContext::setContextValue("SpecCalibrateSetWidgetType",  "HSpecCalibrateSetWidget2");
    HAppContext::setContextValue("AdjustSetWidgetType",         "HAdjustSetWidget2");
    HAppContext::setContextValue("GradeOptional",               QStringList() << "[实测电压]" << "[实测电流]" << "[反向漏流]" << "[电功率]" << "[光强度]" << "[光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标]");
    HAppContext::setContextValue("QualityOptional",             QStringList() << "[实测电压]" << "[实测电流]" << "[反向漏流]" << "[电功率]" << "[光强度]" << "[光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标x]" << "[色坐标y]");
    HAppContext::setContextValue("AdjustOptional",              QStringList() << "[实测电压]" << "[实测电流]" << "[光强度]" << "[光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[显色指数R9]" << "[色坐标x]" << "[色坐标y]");
    HAppContext::setContextValue("TrendOptional",               QStringList() << "[实测电压]" << "[实测电流]" << "[电功率]" << "[光强度]" << "[光通量]"  << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[色坐标x]" << "[色坐标y]" << "[显色指数Ra]" << "[显色指数R9]");
}

HBuilder2000DC::HBuilder2000DC(QObject *parent) :
    HAbstractBuilder(*new HBuilder2000DCPrivate, parent)
{
}

HBuilder2000DC::HBuilder2000DC(HBuilder2000DCPrivate &p, QObject *parent) :
    HAbstractBuilder(p, parent)
{
}

HBuilder2000DC::~HBuilder2000DC() = default;

QString HBuilder2000DC::typeName()
{
    return "HBuilder2000DC";
}

void HBuilder2000DC::buildConfigManage()
{
    Q_D(HBuilder2000DC);
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

        auto luminousItem = d->dataFactory->createLuminousCalibrateItem("HLuminousCalibrateItem");
        auto luminous = d->dataFactory->createLuminousCalibrate("HLuminousCalibrate");
        auto luminouss = d->dataFactory->createLuminousCalibrateCollection("HLuminousCalibrateCollection");
        luminousItem->setData("[项类型]", "[光强度]");
        luminous->insert("[光强度]", luminousItem);
        luminous->setTotalGears(5);
        luminouss->insert("模块1", luminous);

        auto chromatisms = d->dataFactory->createChromatismCollection("HChromatismCollection");
        chromatisms->dataStream()->readFile(":/dat/Chromatism.hcc");

        d->configManage->setContain(IConfigManage::ContainSpec
                                    | IConfigManage::ContainElec
                                    | IConfigManage::ContainLuminous
                                    | IConfigManage::ContainChromatism
                                    | IConfigManage::ContainGrade
                                    | IConfigManage::ContainAdjust
                                    | IConfigManage::ContainQuality);
        d->configManage->setSpecCalibrateCollection(specs);
        d->configManage->setElecCalibrateCollection(elecs);
        d->configManage->setLuminousCalibrateCollection(luminouss);
        d->configManage->setChromatismCollection(chromatisms);
        d->configManage->setGradeCollection(d->dataFactory->createGradeCollection("HGradeCollection"));
        d->configManage->setAdjustCollection(d->dataFactory->createAdjustCollection("HAdjustCollection"));
        d->configManage->addQualityCollection("Spec", d->dataFactory->createQualityCollection("HQualityCollection"));
    }
    HAppContext::setContextPointer("IConfigManage", d->configManage);
}

void HBuilder2000DC::buildTestData()
{
    Q_D(HBuilder2000DC);
    auto data = d->dataFactory->createTestData("HTestData");
    auto product = d->dataFactory->createTestData("HTestProduct");
    auto elec = d->dataFactory->createTestData("HTestElec");
    auto luminous = d->dataFactory->createTestData("HTestLuminous");
    auto spec = d->dataFactory->createTestSpec("HTestSpec");
    spec->setCalibrate(d->configManage->specCalibrate("1"));
    elec->setCalibrate(d->configManage->elecCalibrateCollection());
    elec->setData("[输出电压]", 10);
    luminous->setCalibrate(d->configManage->luminousCalibrateCollection());
    luminous->setData("[光测试类型]", "[光强度]");
    data->setSuccessor(product)->setSuccessor(luminous)->setSuccessor(elec)->setSuccessor(spec);
    HAppContext::setContextPointer("ITestData", data);
    HAppContext::setContextPointer("ITestProduct", product);
    HAppContext::setContextPointer("ITestLuminous", luminous);
    HAppContext::setContextPointer("ITestElec", elec);
    HAppContext::setContextPointer("ITestSpec", spec);
}

void HBuilder2000DC::buildTemplate()
{
    Q_D(HBuilder2000DC);
    auto textExport = d->dataFactory->createTextExport("HTextExport");
    auto specTextTemplate = d->guiFactory->createTextExportTemplate("HSpecTextExportTemplate");
    auto print = d->dataFactory->createPrint("HPrint");
    auto tagPrintTemplate = d->guiFactory->createPrintTemplate("HTagPrintTemplate");
    auto specPrintTemplate = new HSpecPrintTemplate2000DC(this);
    specPrintTemplate->initialize();
    HAppContext::setContextPointer("ITextExport", textExport);
    HAppContext::setContextPointer("ISpecTextExportTemplate", specTextTemplate);
    HAppContext::setContextPointer("IPrint", print);
    HAppContext::setContextPointer("ISpecPrintTemplate", specPrintTemplate);
    HAppContext::setContextPointer("ITagPrintTemplate", tagPrintTemplate);
}

void HBuilder2000DC::buildDevice()
{
    Q_D(HBuilder2000DC);
#ifdef SIMULATE // 模拟设备
    auto device1 = d->communicateFactory->createDevice("HSpecSimulateDevice");
    auto device2 = d->communicateFactory->createDevice("HSimulateDevice");
    auto protocol1 = d->communicateFactory->createProtocol("HLittleProtocol");
    auto protocol2 = d->communicateFactory->createProtocol("HLittleProtocol");
    protocol1->setDevice(device1);
    protocol2->setDevice(device2);
#else
    auto protocol1 = d->communicateFactory->createProtocol(deployItem("CcdProtocol"));
    auto protocol2 = d->communicateFactory->createProtocol("HSl1000Protocol");
#endif
    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
    protocols->insert("Spec", protocol1);
    protocols->insert("Else", protocol2);
    HAppContext::setContextPointer("IProtocolCollection", protocols);
}

void HBuilder2000DC::buildThread()
{
    Q_D(HBuilder2000DC);
    auto thread = d->controllerFactory->createThread("HIntegrateThread");
    auto threads = d->controllerFactory->createThreadCollection("HThreadCollection");
    threads->insert("1", thread);
    HAppContext::setContextPointer("IThreadCollection", threads);
}

void HBuilder2000DC::buildModel()
{
    Q_D(HBuilder2000DC);
    auto model = d->controllerFactory->createModel("HIntegrateModel");
    HAppContext::setContextPointer("IModel", model);
}

void HBuilder2000DC::buildMemento()
{
    Q_D(HBuilder2000DC);
    auto mementos = d->controllerFactory->createMementoCollection("HMementoCollection");
    if (!mementos->readFile(QString("%1.tmp").arg(QApplication::applicationName())) || !mementos->contains("Spec"))
    {
        auto memento = d->controllerFactory->createMemento("HMemento");
        memento->setDataType(QStringList() << "[积分时间]" << "[输出电流_档位]" << "[实测电流_档位]" << "[输出电压]" << "[输出电流]" << "[反向电压]" << "[光测试类型]" << "[光档位]");
        mementos->insert("Spec", memento);
    }
    HAppContext::setContextPointer("IMementoCollection", mementos);
}

void HBuilder2000DC::buildDatabase()
{
    Q_D(HBuilder2000DC);
    auto db = d->sqlFactory->createDatabase("HSqliteDatabase");
    db->openConnection();
    HSqlHelper::updateSpecTable(db);

    auto group = QStringList() << "|产品信息2|" << "|环境信息|" << "|时间信息2|" << "|直流电信息|" << "|光度信息|" << "|光谱信息3|" << "|色容差信息|" << "|光合信息|" << "|TM30信息|";
    auto field = QStringList() << "ID" << HSql::membership(group);
    auto model = createSqlTableModel("Spec", field);
    db->insertTableModel(model);
}

void HBuilder2000DC::buildMenu()
{
    Q_D(HBuilder2000DC);
    QVariantMap param[3];
    param[0].insert("authority", 1);
    param[1].insert("property", param[0]);
    param[2].insert("printTemplate",        "ISpecPrintTemplate");
    param[2].insert("printSettingDialog",   "HSpecPrintSettingDialog");
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
    quality->menuAction()->setProperty("authority", 1);
    device->menuAction()->setProperty("authority", 1);
    calibrate->addAction(d->guiFactory->createAction(tr("光谱定标(&S)..."), "HSpecCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("电定标(&E)..."), "HElecCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("光定标(&E)..."), "HLuminousCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("光通量自吸收配置(&L)..."), "HSpecLuminousHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("色温配置(&T)..."), "HSpecTcHandler"));
    grade->addAction(d->guiFactory->createAction(tr("分级数据配置(&E)..."), "HGradeEditHandler"));
    grade->addAction(d->guiFactory->createAction(tr("分级数据选择(&S)..."), "HGradeSelectHandler"));
    adjust->addAction(d->guiFactory->createAction(tr("调整数据配置(&E)..."), "HAdjustEditHandler", param[1]));
    adjust->addAction(d->guiFactory->createAction(tr("调整数据选择(&S)..."), "HAdjustSelectHandler"));
    quality->addAction(d->guiFactory->createAction(tr("品质数据配置(&E)..."), "HQualityEditHandler"));
    quality->addAction(d->guiFactory->createAction(tr("品质数据选择(&S)..."), "HQualitySelectHandler"));
    device->addAction(d->guiFactory->createAction(tr("从设备读取数据(&G)..."), "HImportDeviceHandler"));
    device->addAction(d->guiFactory->createAction(tr("写入数据到设备(&S)..."), "HExportDeviceHandler"));
    device->addAction(d->guiFactory->createAction(tr("导入标准曲线(&I)..."), "HImportCurveHandler"));
    device->addAction(d->guiFactory->createAction(tr("导出标准曲线(&E)..."), "HExportCurveHandler"));
    test->addAction(d->guiFactory->createAction(tr("老化测试(&I)..."), "HTrendTestHandler"));
    test->addAction(d->guiFactory->createAction(tr("IV测试(&I)..."), "HIVTestHandler"));
    database->addAction(d->guiFactory->createAction(tr("产品信息配置(&P)..."), "HProductEditHandler"));
    database->addAction(d->guiFactory->createAction(tr("数据打印配置(&P)..."), "HPrintSettingHandler", param[2]));
    database->addAction(d->guiFactory->createAction(tr("数据库浏览(&B)..."), "HSqlBrowserHandler"));
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

void HBuilder2000DC::buildTestWidget()
{
    ITestWidget *widget = new HTestWidget2000DC;
//    widget->setVisible(false);
    HAppContext::setContextPointer("ITestWidget", widget);
}
