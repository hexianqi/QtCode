#include "HBuilder2000DC_p.h"
#include "HSpecPrintTemplate2000DC.h"
#include "HTestWidget2000DC.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IDataFactory.h"
#include "HeData/IDataStream.h"
#include "HeData/ISpecCalibrate.h"
#include "HeData/ISpecCalibrateCollection.h"
#include "HeData/IChromatismCollection.h"
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
#include "HeSql/ISqlFactory.h"
#include "HeSql/ISqlDatabase.h"
#include "HeSql/ISqlTableModel.h"
#include "HeSql/ISqlBrowser.h"
#include "HeSql/ISqlHandle.h"
#include "HeSql/ISqlPrint.h"
#include "HeSql/IProductInfo.h"
#include "HeSql/HSqlHelper.h"
#include "HeGui/IGuiFactory.h"
#include "HeGui/IMainWindow.h"
#include "HeGui/HAction.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>
#include <QtCore/QDebug>

HBuilder2000DCPrivate::HBuilder2000DCPrivate()
{
    deploy.insert("SpecFitting",    "HSpecFittingPolynom"); // HSpecFittingPolynom: 多项式拟合; HSpecFittingLinear : 插值拟合
    deploy.insert("CcdProtocol",    "HCcdProtocol01");      // HCcdProtocol01:1305; HCcdProtocol02:554b

    sqlField = QStringList() << "ID" << "Manufacturer" << "ProductName" << "ProductModel" << "SampleNumber" << "Tester" << "TestInstitute"
                             << "Temperature" << "Humidity" << "TestDate" << "TestTime"
                             << "OutputVoltage" << "OutputCurrent" << "MeasuredVoltage" << "MeasuredCurrent" << "ReverseVoltage" << "ReverseCurrent" << "ElecPower"
                             << "LuminousFlux" << "LuminousPower" << "LuminousEfficiency"
                             << "PeakWave" << "PeakBandwidth" << "DominantWave"
                             << "ColorTemperature" << "ColorPurity"
                             << "CC_x" << "CC_y" << "CC_up" << "CC_vp" << "Duv"
                             << "RedRatio" << "GreenRadio" << "BlueRatio"
                             << "Ra" << "R9" << "Rx" << "SDCM"
                             << "Photon380_780" << "Photon400_700" << "Photon700_800" << "PPF" << "PRF" << "PPFE" << "FluorescenceEfficiency" << "FluorescenceRatio"
                             << "EnergyGraph";
    HAppContext::setContextValue("SpecCalibrateSetWidgetType",  "HSpecCalibrateSetWidget2");
    HAppContext::setContextValue("AdjustSetWidgetType",         "HAdjustSetWidget2");
    HAppContext::setContextValue("GradeOptionals",              QStringList() << "[实测电压]" << "[实测电流]" << "[反向漏流]" << "[电功率]" << "[光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标]");
    HAppContext::setContextValue("QualityOptionals",            QStringList() << "[实测电压]" << "[实测电流]" << "[反向漏流]" << "[电功率]" << "[光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标x]" << "[色坐标y]");
    HAppContext::setContextValue("AdjustOptionals",             QStringList() << "[实测电压]" << "[实测电流]" << "[光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[显色指数R9]" << "[色坐标x]" << "[色坐标y]");
}

HBuilder2000DC::HBuilder2000DC(QObject *parent) :
    HAbstractBuilder(*new HBuilder2000DCPrivate, parent)
{
}

HBuilder2000DC::HBuilder2000DC(HBuilder2000DCPrivate &p, QObject *parent) :
    HAbstractBuilder(p, parent)
{
}

HBuilder2000DC::~HBuilder2000DC()
{
    qDebug() << __func__;
}

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
        {
            auto fit = d->dataFactory->createSpecFitting(deployItem("SpecFitting"));
            auto spec = d->dataFactory->createSpecCalibrate("HSpecCalibrate");
            spec->setFitting(fit);
            specs->insert("1", spec);
        }

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
        d->configManage->setQualityCollection(d->dataFactory->createQualityCollection("HQualityCollection"));
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
    auto print = d->dataFactory->createPrint("HPrint");
    auto expor = d->dataFactory->createTextExport("HTextExport");
    auto spec = new HSpecPrintTemplate2000DC(this);
    auto tag = d->guiFactory->createPrintTemplate("HTagPrintTemplate");
    auto text = d->guiFactory->createTextExportTemplate("HSpecTextExportTemplate");
    HAppContext::setContextPointer("IPrint", print);
    HAppContext::setContextPointer("ITextExport", expor);
    HAppContext::setContextPointer("ISpecPrintTemplate", spec);
    HAppContext::setContextPointer("ITagPrintTemplate", tag);
    HAppContext::setContextPointer("ISpecTextExportTemplate", text);
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
    auto memento = d->controllerFactory->createMemento("HMemento");
    memento->setDataTypes(QStringList() << "[积分时间]" << "[输出电流_档位]" << "[实测电流_档位]" << "[输出电压]" << "[输出电流]" << "[反向电压]" << "[光测试类型]" << "[光档位]");
    memento->readFile(QString("%1.tmp").arg(QApplication::applicationName()));
    HAppContext::setContextPointer("IMementoTest", memento);
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
    if (db->contains("Spec"))
    {
        auto version = HSqlHelper::getVersion("Spec");
        // 1.1.1.2 添加列R9
        if (version < 0x01010102)
            HSqlHelper::addColumn("Spec", "R9");
        // 1.1.1.3 添加列（光合）
        if (version < 0x01010103)
            HSqlHelper::addColumn("Spec", QStringList() << "Photon380_780" << "Photon400_700" << "Photon700_800" << "PPF" << "PRF" << "PPFE" << "FluorescenceEfficiency" << "FluorescenceRatio");
        // 1.1.1.4 添加列SDCM
        if (version < 0x01010104)
            HSqlHelper::addColumn("Spec", "SDCM");
    }
    HSqlHelper::setVersion("Spec", 0x01010104);

    auto model = d->sqlFactory->createTableModel("HSqlTableModel");
    auto info = d->sqlFactory->createProductInfo("HProductInfo");
    auto handle = d->sqlFactory->createHandle("HSqlHandle");
    auto print = d->sqlFactory->createPrint("HIntegrateSqlPrint");
    auto browser = d->sqlFactory->createBrowser("HSqlBrowser", d->mainWindow);
    model->setTableField("Spec", d->sqlField);
    info->setRelationTableName("Spec");
    handle->setModel(model);
    handle->setProductInfo(info);
    handle->setFieldFind(find);
    print->setModel(model);
    print->setFieldExportExcel(exportExcel);
    browser->setModel(model);
    browser->setRecordHandle(handle);
    browser->setRecordPrint(print);
    db->insertTableModel(model);
    HAppContext::setContextPointer("ISqlHandle", handle);
    HAppContext::setContextPointer("ISqlPrint", print);
    HAppContext::setContextPointer("ISqlBrowser", browser);
}

void HBuilder2000DC::buildMenu()
{
    Q_D(HBuilder2000DC);
    QVariantMap param[2];
    param[1].insert("authority", 1);
    param[0].insert("property", param[1]);
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
    adjust->addAction(d->guiFactory->createAction(tr("调整数据配置(&E)..."), "HAdjustEditHandler", param[0]));
    adjust->addAction(d->guiFactory->createAction(tr("调整数据选择(&S)..."), "HAdjustSelectHandler"));
    quality->addAction(d->guiFactory->createAction(tr("品质数据配置(&E)..."), "HQualityEditHandler"));
    quality->addAction(d->guiFactory->createAction(tr("品质数据选择(&S)..."), "HQualitySelectHandler"));
    device->addAction(d->guiFactory->createAction(tr("从设备读取数据(&G)..."), "HImportDeviceHandler"));
    device->addAction(d->guiFactory->createAction(tr("写入数据到设备(&S)..."), "HExportDeviceHandler"));
    device->addAction(d->guiFactory->createAction(tr("导入标准曲线(&I)..."), "HImportCurveHandler"));
    device->addAction(d->guiFactory->createAction(tr("导出标准曲线(&E)..."), "HExportCurveHandler"));
    test->addAction(d->guiFactory->createAction(tr("IV测试(&I)..."), "HIVTestHandler"));
    database->addAction(d->guiFactory->createAction(tr("产品信息配置(&P)..."), "HProductEditHandler"));
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
    d->mainWindow->setAuthority(0);
}

void HBuilder2000DC::buildTestWidget()
{
    ITestWidget *widget = new HTestWidget2000DC;
//    widget->setVisible(false);
    HAppContext::setContextPointer("ITestWidget", widget);
}
