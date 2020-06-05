#include "HBuilder2000DC_p.h"
#include "HTestWidget2000DC.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IDataFactory.h"
#include "HeData/IFileStream.h"
#include "HeData/ISpecCalibrate.h"
#include "HeData/ISpecCalibrateCollection.h"
#include "HeData/IElecCalibrate.h"
#include "HeData/IElecCalibrateCollection.h"
#include "HeData/IChromatismCollection.h"
#include "HeData/ITestSpec.h"
#include "HeData/ITestElec.h"
#include "HeData/ITestLuminous.h"
#include "HeData/ILuminousCalibrate.h"
#include "HeData/ILuminousCalibrateItem.h"
#include "HeData/ILuminousCalibrateCollection.h"
#include "HeCommunicate/ICommunicateFactory.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeCommunicate/IDevice.h"
#include "HeController/IControllerFactory.h"
#include "HeController/IThreadCollection.h"
#include "HeSql/ISqlFactory.h"
#include "HeSql/ISqlDatabase.h"
#include "HeSql/ISqlTableModel.h"
#include "HeSql/ISqlBrowser.h"
#include "HeSql/ISqlHandle.h"
#include "HeSql/ISqlPrint.h"
#include "HeSql/IProductInfo.h"
#include "HeGui/IGuiFactory.h"
#include "HeGui/IMainWindow.h"
#include "HeGui/HAction.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>
#include <QtCore/QDebug>

HBuilder2000DCPrivate::HBuilder2000DCPrivate(IMainWindow *p) :
    HAbstractBuilderPrivate(p)
{
    deploy.insert("SpecFitting",    "HSpecFittingPolynom"); // HSpecFittingPolynom: 多项式拟合; HSpecFittingLinear : 插值拟合
    deploy.insert("Protocol",       "HCcdProtocol01");      // HCcdProtocol01:1305; HCcdProtocol02:554b

    sqlField = QStringList() << "ID" << "Manufacturer" << "ProductName" << "ProductModel" << "SampleNumber" << "Tester" << "TestInstitute"
                             << "Temperature" << "Humidity" << "TestDate" << "TestTime"
                             << "OutputVoltage" << "OutputCurrent" << "MeasuredVoltage" << "MeasuredCurrent" << "ReverseVoltage" << "ReverseCurrent" << "ElecPower"
                             << "LuminousFlux" << "LuminousPower" << "LuminousEfficiency"
                             << "PeakWave" << "PeakBandwidth" << "DominantWave"
                             << "ColorTemperature" << "ColorPurity"
                             << "CC_x" << "CC_y" << "CC_up" << "CC_vp" << "Duv"
                             << "RedRatio" << "GreenRadio" << "BlueRatio"
                             << "Ra" << "Rx" << "EnergyGraph";
    HAppContext::setContextValue("GradeOptionals",      QStringList() << "[实测电压]" << "[实测电流]" << "[反向漏流]" << "[电功率]" << "[光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数]" << "[色坐标]");
    HAppContext::setContextValue("QualityOptionals",    QStringList() << "[实测电压]" << "[实测电流]" << "[反向漏流]" << "[电功率]" << "[光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数]" << "[色坐标x]" << "[色坐标y]");
    HAppContext::setContextValue("AdjustOptionals",     QStringList() << "[光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数]" << "[色坐标x]" << "[色坐标y]");
}

HBuilder2000DC::HBuilder2000DC(IMainWindow *parent) :
    HAbstractBuilder(*new HBuilder2000DCPrivate(parent), parent)
{
}

HBuilder2000DC::~HBuilder2000DC()
{
    qDebug() << __func__;
}

void HBuilder2000DC::initialize(QVariantMap /*param*/)
{

}

QString HBuilder2000DC::typeName()
{
    return "HBuilder2000DC";
}

void HBuilder2000DC::buildConfigManage()
{
    Q_D(HBuilder2000DC);
    d->configManage = d->dataFactory->createConfigManage("HConfigManage");
    if (!d->configManage->fileStream()->readFile(d->configFileName))
    {
        auto specs = d->dataFactory->createSpecCalibrateCollection("HSpecCalibrateCollection");
        if (!specs->fileStream()->readFile(":/dat/Spectrum.hcs"))
        {
            auto fit = d->dataFactory->createSpecFitting(deployItem("SpecFitting"));
            auto spec = d->dataFactory->createSpecCalibrate("HSpecCalibrate");
            spec->setFitting(fit);
            specs->insert("1", spec);
        }

        QVariantMap param[6];
        param[0].insert("itemClassName",    "HElecCalibrateItem");
        param[0].insert("itemTypeList",     QStringList() << "[输出电压]");
        param[1].insert("itemClassName",    "HElecCalibrateItem");
        param[1].insert("itemTypeList",     QStringList() << "[输出电流1]" << "[输出电流2]");
        param[2].insert("itemClassName",    "HElecCalibrateItem");
        param[2].insert("itemTypeList",     QStringList() << "[实测电压]");
        param[3].insert("itemClassName",    "HElecCalibrateItem");
        param[3].insert("itemTypeList",     QStringList() << "[实测电流]");
        param[4].insert("itemClassName",    "HElecCalibrateItem");
        param[4].insert("itemTypeList",     QStringList() << "[反向电压]");
        param[5].insert("itemClassName",    "HElecCalibrateItem");
        param[5].insert("itemTypeList",     QStringList() << "[反向漏流]");
        auto elec = d->dataFactory->createElecCalibrate("HElecCalibrate");
        elec->setItemCollection(OutputVoltage,   d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[0]));
        elec->setItemCollection(OutputCurrent,   d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[1]));
        elec->setItemCollection(MeasuredVoltage, d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[2]));
        elec->setItemCollection(MeasuredCurrent, d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[3]));
        elec->setItemCollection(ReverseVoltage,  d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[4]));
        elec->setItemCollection(ReverseCurrent,  d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[5]));
        auto elecs = d->dataFactory->createElecCalibrateCollection("HElecCalibrateCollection");
        elecs->insert("模块1", elec);

        auto luminousItem = d->dataFactory->createLuminousCalibrateItem("HLuminousCalibrateItem");
        luminousItem->setData("[项类型]", "[光通量]");
        luminousItem->setTotalGears(5);
        auto luminous = d->dataFactory->createLuminousCalibrate("HLuminousCalibrate");
        luminous->insert("[光通量]", luminousItem);
        auto luminouss = d->dataFactory->createLuminousCalibrateCollection("HLuminousCalibrateCollection");
        luminouss->insert("模块1", luminous);

        auto chromatisms = d->dataFactory->createChromatismCollection("HChromatismCollection");
        chromatisms->fileStream()->readFile(":/dat/Chromatism.hcc");

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
        d->configManage->setQualityCollection(d->dataFactory->createQualityCollection("HQualityCollection"));
    }
    HAppContext::setContextPointer("IConfigManage", d->configManage);
}

void HBuilder2000DC::buildTestData()
{
    Q_D(HBuilder2000DC);
    auto data = d->dataFactory->createTestData("HTestData");
    auto other = d->dataFactory->createTestData("HTestData");
    auto spec = d->dataFactory->createTestSpec("HTestSpec");
    auto elec = d->dataFactory->createTestElec("HTestElec");
    auto luminous = d->dataFactory->createTestLuminous("HTestLuminous");

    spec->setSuccessor(other);
    spec->setCalibrate(d->configManage->specCalibrate("1"));
    elec->setSuccessor(spec);
    elec->setCalibrate(d->configManage->elecCalibrateCollection());
    elec->setData("[输出电压]", 10);
    luminous->setSuccessor(elec);
    luminous->setCalibrate(d->configManage->luminousCalibrateCollection());
    data->setSuccessor(luminous);
    HAppContext::setContextPointer("ITestData", data);
    HAppContext::setContextPointer("ITestLuminous", luminous);
    HAppContext::setContextPointer("ITestElec", elec);
    HAppContext::setContextPointer("ITestSpec", spec);
    HAppContext::setContextPointer("ITestOther", other);
}

void HBuilder2000DC::buildDevice()
{
    Q_D(HBuilder2000DC);
    // 模拟设备
    auto device1 = d->communicateFactory->createDevice("HSpecSimulateDevice");
    auto device2 = d->communicateFactory->createDevice("HSlSimulateDevice");
    auto protocol1 = d->communicateFactory->createProtocol("HLittleProtocol");
    auto protocol2 = d->communicateFactory->createProtocol("HLittleProtocol");
    protocol1->setDevice(device1);
    protocol2->setDevice(device2);
//    // 真实设备
//    auto protocol1 = d->communicateFactory->createProtocol(deployItem("Protocol"));
//    auto protocol2 = d->communicateFactory->createProtocol("HSl1000Protocol");
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
    d->model = d->controllerFactory->createModel("HIntegrateModel");
    HAppContext::setContextPointer("IModel", d->model);
}

void HBuilder2000DC::buildDatabase()
{
    Q_D(HBuilder2000DC);
    auto find = d->sqlField;
    auto exportExcel = d->sqlField;
    find.removeFirst();
    find.removeLast();
    find.removeLast();
    exportExcel.removeLast();

    auto db = d->sqlFactory->createDatabase("HSqlDatabase");
    db->openDatabase(QString("%1.db").arg(QApplication::applicationName()));
    auto model = d->sqlFactory->createTableModel("HSqlTableModel");
    auto info = d->sqlFactory->createProductInfo("HProductInfo");
    auto handle = d->sqlFactory->createHandle("HSqlHandle");
    auto print = d->sqlFactory->createPrint("HIntegrateSqlPrint");
    auto browser = d->sqlFactory->createBrowser("HSqlBrowser", d->mainWindow);
    model->setField(d->sqlField);
    model->setTable("Spec");
    info->setRelationTableName("Spec");
    handle->setModel(model);
    handle->setProductInfo(info);
    handle->setFieldFind(find);
    print->setModel(model);
    print->setFieldExportExcel(exportExcel);
    browser->setModel(model);
    browser->setRecordHandle(handle);
    browser->setRecordPrint(print);
    db->insertTableModel("Spec", model);
    HAppContext::setContextPointer("ISqlHandle", handle);
    HAppContext::setContextPointer("ISqlPrint", print);
    HAppContext::setContextPointer("ISqlBrowser", browser);
}

void HBuilder2000DC::buildMenu()
{
    Q_D(HBuilder2000DC);
    auto calibrate = new QMenu(tr("定标(&C)"));
    auto grade = new QMenu(tr("分级(&G)"));
    auto adjust = new QMenu(tr("调整(&A)"));
    auto quality = new QMenu(tr("品质(&Q)"));
    auto test = new QMenu(tr("其他测试(&E)"));
    auto database = new QMenu(tr("数据库(&D)"));
    calibrate->addAction(d->guiFactory->createAction(tr("光谱定标(&S)..."), "HSpecCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("电定标(&E)..."), "HElecCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("光定标(&E)..."), "HLuminousCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("光通量自吸收配置(&L)..."), "HSpecLuminousHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("色温配置(&T)..."), "HSpecTcHandler"));
    grade->addAction(d->guiFactory->createAction(tr("分级数据配置(&E)..."), "HGradeEditHandler"));
    grade->addAction(d->guiFactory->createAction(tr("分级数据选择(&S)..."), "HGradeSelectHandler"));
    adjust->addAction(d->guiFactory->createAction(tr("调整数据配置(&E)..."), "HAdjustEditHandler"));
    adjust->addAction(d->guiFactory->createAction(tr("调整数据选择(&S)..."), "HAdjustSelectHandler"));
    quality->addAction(d->guiFactory->createAction(tr("品质数据配置(&E)..."), "HQualityEditHandler"));
    quality->addAction(d->guiFactory->createAction(tr("品质数据选择(&S)..."), "HQualitySelectHandler"));
    test->addAction(d->guiFactory->createAction(tr("IV测试(&I)..."), "HIVTestHandler"));
    database->addAction(d->guiFactory->createAction(tr("产品信息配置(&P)..."), "HProductInfoEditHandler"));
    database->addAction(d->guiFactory->createAction(tr("数据库浏览(&B)..."), "HSqlBrowserHandler"));
    d->mainWindow->insertMenu(calibrate);
    d->mainWindow->insertMenu(grade);
    d->mainWindow->insertMenu(adjust);
    d->mainWindow->insertMenu(quality);
    d->mainWindow->insertMenu(test);
    d->mainWindow->insertMenu(database);
}

void HBuilder2000DC::buildTestWidget()
{
    ITestWidget *widget = new HTestWidget2000DC;
    widget->setVisible(false);
    HAppContext::setContextPointer("ITestWidget", widget);
}
