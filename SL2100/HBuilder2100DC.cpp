#include "HBuilder2100DC_p.h"
#include "HThread2100DC.h"
#include "HModel2100DC.h"
#include "HSpecPrintTemplate2100DC.h"
#include "HTestWidget2100DC.h"
#include "HDaXinProtocol.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IDataFactory.h"
#include "HeData/IDataStream.h"
#include "HeData/ISpecCalibrateCollection.h"
#include "HeData/ISpecCalibrate.h"
#include "HeData/IChromatismCollection.h"
#include "HeData/ITestSpec.h"
#include "HeCommunicate/ICommunicateFactory.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeController/IControllerFactory.h"
#include "HeController/IThreadCollection.h"
#include "HeController/IMemento.h"
#include "HeSql/ISqlFactory.h"
#include "HeSql/ISqlDatabase.h"
#include "HeSql/ISqlTableModel.h"
#include "HeSql/ISqlBrowser.h"
#include "HeSql/ISqlHandle.h"
#include "HeSql/ISqlOutput.h"
#include "HeSql/HSql.h"
#include "HeSql/HSqlHelper.h"
#include "HeGui/IGuiFactory.h"
#include "HeGui/IMainWindow.h"
#include "HeGui/HAction.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>

HBuilder2100DCPrivate::HBuilder2100DCPrivate()
{
    deploy.insert("SpecFitting",    "HSpecFittingPolynom"); // HSpecFittingPolynom: 多项式拟合; HSpecFittingLinear : 插值拟合
    deploy.insert("CcdProtocol",    "HCcdProtocol01");      // HCcdProtocol01:1305; HCcdProtocol02:554b

    sqlField = QStringList() << "ID" << "Manufacturer" << "ProductName" << "ProductModel" << "SampleNumber" << "Tester" << "TestInstitute"
                             << "Temperature" << "Humidity" << "TestDate" << "TestTime"
                             << "OutputVoltage" << "OutputCurrent" << "MeasuredVoltage" << "MeasuredCurrent" << "ElecPower"
                             << "LuminousFluxSpec" << "LuminousPower" << "LuminousEfficiency"
                             << "PeakWave" << "PeakBandwidth" << "DominantWave"
                             << "ColorTemperature" << "ColorPurity"
                             << "CC_x" << "CC_y" << "CC_up" << "CC_vp" << "Duv"
                             << "RedRatio" << "GreenRadio" << "BlueRatio"
                             << "Ra" << "R9" << "Rx" << "SDCM"
                             << "Photon380_780" << "Photon400_700" << "Photon700_800" << "PPF" << "PRF" << "PPFE" << "FluorescenceEfficiency" << "FluorescenceRatio"
                             << "EnergyGraph" << "ReflectGraph"
                             << "TM30_Rf" << "TM30_Rg" << "TM30_Rfi"
                             << "TM30_hj_Rf" << "TM30_hj_Rcs" << "TM30_hj_Rhs"
                             << "TM30_hj_at" << "TM30_hj_bt" << "TM30_hj_ar" << "TM30_hj_br"
                             << "TM30_hj_atn" << "TM30_hj_btn" << "TM30_hj_arn" << "TM30_hj_brn";
    HAppContext::setContextValue("SpecCalibrateSetWidgetType",  "HSpecCalibrateSetWidget2");
    HAppContext::setContextValue("AdjustSetWidgetType",         "HAdjustSetWidget2");
    HAppContext::setContextValue("GradeOptionals",              QStringList() << "[实测电压]" << "[实测电流]" << "[电功率]" << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标]");
    HAppContext::setContextValue("QualityOptionals",            QStringList() << "[实测电压]" << "[实测电流]" << "[电功率]" << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标x]" << "[色坐标y]");
    HAppContext::setContextValue("AdjustOptionals",             QStringList() << "[实测电压]" << "[实测电流]" << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[显色指数R9]" << "[色坐标x]" << "[色坐标y]");
}

HBuilder2100DC::HBuilder2100DC(QObject *parent) :
    HAbstractBuilder(*new HBuilder2100DCPrivate, parent)
{
}

HBuilder2100DC::~HBuilder2100DC() = default;

QString HBuilder2100DC::typeName()
{
    return "HBuilder2100DC";
}

void HBuilder2100DC::buildConfigManage()
{
    Q_D(HBuilder2100DC);
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

void HBuilder2100DC::buildTestData()
{
    Q_D(HBuilder2100DC);
    auto data = d->dataFactory->createTestData("HTestData");
    auto product = d->dataFactory->createTestData("HTestProduct");
    auto spec = d->dataFactory->createTestSpec("HTestSpec");
    spec->setCalibrate(d->configManage->specCalibrate("1"));
    data->setSuccessor(product)->setSuccessor(spec);
    HAppContext::setContextPointer("ITestData", data);
    HAppContext::setContextPointer("ITestProduct", product);
    HAppContext::setContextPointer("ITestSpec", spec);
}

void HBuilder2100DC::buildDevice()
{
    Q_D(HBuilder2100DC);
#ifdef SIMULATE // 模拟设备
    auto device1 = d->communicateFactory->createDevice("HSpecSimulateDevice");
    auto device2 = d->communicateFactory->createDevice("HSimulateDevice");
    auto protocol1 = d->communicateFactory->createProtocol("HLittleProtocol");
    auto protocol2 = d->communicateFactory->createProtocol("HLittleProtocol");
    protocol1->setDevice(device1);
    protocol2->setDevice(device2);
#else
    auto protocol1 = d->communicateFactory->createProtocol(deployItem("CcdProtocol"));
    //auto protocol2 = d->communicateFactory->createProtocol("HDaXinProtocol");
    auto protocol2 = new HDaXinProtocol();
#endif
    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
    protocols->insert("Spec", protocol1);
    protocols->insert("Elec", protocol2);
    HAppContext::setContextPointer("IProtocolCollection", protocols);
}

void HBuilder2100DC::buildTemplate()
{
    Q_D(HBuilder2100DC);
    auto expor = d->dataFactory->createTextExport("HTextExport");
    auto text = d->guiFactory->createTextExportTemplate("HSpecTextExportTemplate");
    auto print = d->dataFactory->createPrint("HPrint");
    auto tag = d->guiFactory->createPrintTemplate("HTagPrintTemplate");
    auto spec = new HSpecPrintTemplate2100DC(this);
    spec->initialize();
    HAppContext::setContextPointer("ITextExport", expor);
    HAppContext::setContextPointer("ISpecTextExportTemplate", text);
    HAppContext::setContextPointer("IPrint", print);
    HAppContext::setContextPointer("ISpecPrintTemplate", spec);
    HAppContext::setContextPointer("ITagPrintTemplate", tag);
}

void HBuilder2100DC::buildThread()
{
    Q_D(HBuilder2100DC);
    auto thread = new HThread2100DC(this);
    auto threads = d->controllerFactory->createThreadCollection("HThreadCollection");
    threads->insert("1", thread);
    HAppContext::setContextPointer("IThreadCollection", threads);
}

void HBuilder2100DC::buildModel()
{
    auto model = new HModel2100DC(this);
    HAppContext::setContextPointer("IModel", model);
}

void HBuilder2100DC::buildMemento()
{
    Q_D(HBuilder2100DC);
    auto memento = d->controllerFactory->createMemento("HMemento");
    memento->setDataTypes(QStringList() << "[积分时间]" << "[输出电压]" << "[输出电流]");
    memento->readFile(QString("%1.tmp").arg(QApplication::applicationName()));
    HAppContext::setContextPointer("IMementoTest", memento);
}

void HBuilder2100DC::buildDatabase()
{
    Q_D(HBuilder2100DC);
    auto find = d->sqlField;
    find.removeAll("ID");
    find.removeAll("Rx");
    find.removeAll("EnergyGraph");
    find.removeAll("ReflectGraph");
    find.removeAll("TM30_Rfi");
    find.removeAll("TM30_hj_Rf");
    find.removeAll("TM30_hj_Rcs");
    find.removeAll("TM30_hj_Rhs");
    find.removeAll("TM30_hj_at");
    find.removeAll("TM30_hj_bt");
    find.removeAll("TM30_hj_ar");
    find.removeAll("TM30_hj_br");
    find.removeAll("TM30_hj_atn");
    find.removeAll("TM30_hj_btn");
    find.removeAll("TM30_hj_arn");
    find.removeAll("TM30_hj_arn");

    auto db = d->sqlFactory->createDatabase("HSqlDatabase");
    db->openDatabase(QString("%1.db").arg(QApplication::applicationName()));
    if (db->contains("Spec"))
    {
        auto version = HSqlHelper::getVersion("Spec");
        // 1.1.1.3 添加列（光合）
        if (version < 0x01010103)
            HSqlHelper::addColumn("Spec", HSql::membership("|光合信息|"));
        // 1.1.1.4 添加列SDCM
        if (version < 0x01010104)
            HSqlHelper::addColumn("Spec", "SDCM");
        // 1.1.1.5 添加列TM30
        if (version < 0x01010105)
            HSqlHelper::addColumn("Spec", QStringList() << "ReflectGraph" << HSql::membership("|TM30信息|"));
    }
    HSqlHelper::setVersion("Spec", 0x01010105);

    auto model = d->sqlFactory->createTableModel("HSqlTableModel");
    auto handle = d->sqlFactory->createHandle("HSqlHandle");
    auto output = d->sqlFactory->createOutput("HSqlOutput");
    auto browser = d->sqlFactory->createBrowser("HSqlBrowser", d->mainWindow);
    auto text = HAppContext::getContextPointer<ITextExportTemplate>("ISpecTextExportTemplate");
    auto print = HAppContext::getContextPointer<IPrintTemplate>("ISpecPrintTemplate");
    model->setTableField("Spec", d->sqlField);
    handle->setModel(model);
    handle->setFieldFind(find);
    output->setModel(model);
    output->setTextTemplate(text);
    output->setPrintTemplate(print);
    browser->setModel(model);
    browser->setRecordHandle(handle);
    browser->setRecordOutput(output);
    db->insertTableModel(model);
    HAppContext::setContextPointer("ISqlHandle", handle);
    HAppContext::setContextPointer("ISqlBrowser", browser);
}

void HBuilder2100DC::buildMenu()
{
    Q_D(HBuilder2100DC);
    QVariantMap param[2];
    param[1].insert("authority", 1);
    param[0].insert("property", param[1]);
    auto calibrate = new QMenu(tr("定标(&C)"));
    auto grade = new QMenu(tr("分级(&G)"));
    auto adjust = new QMenu(tr("调整(&A)"));
    auto quality = new QMenu(tr("品质(&Q)"));
    auto test = new QMenu(tr("其他测试(&E)"));
    auto database = new QMenu(tr("数据库(&D)"));
    auto account = new QMenu(tr("账号管理(&M)"));
    calibrate->menuAction()->setProperty("authority", 1);
    grade->menuAction()->setProperty("authority", 1);
    quality->menuAction()->setProperty("authority", 1);
    calibrate->addAction(d->guiFactory->createAction(tr("光谱定标(&S)..."), "HSpecCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("光通量自吸收配置(&L)..."), "HSpecLuminousHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("色温配置(&T)..."), "HSpecTcHandler"));
    grade->addAction(d->guiFactory->createAction(tr("分级数据配置(&E)..."), "HGradeEditHandler"));
    grade->addAction(d->guiFactory->createAction(tr("分级数据选择(&S)..."), "HGradeSelectHandler"));
    adjust->addAction(d->guiFactory->createAction(tr("调整数据配置(&E)..."), "HAdjustEditHandler", param[0]));
    adjust->addAction(d->guiFactory->createAction(tr("调整数据选择(&S)..."), "HAdjustSelectHandler"));
    quality->addAction(d->guiFactory->createAction(tr("品质数据配置(&E)..."), "HQualityEditHandler"));
    quality->addAction(d->guiFactory->createAction(tr("品质数据选择(&S)..."), "HQualitySelectHandler"));
    test->addAction(d->guiFactory->createAction(tr("IV测试(&I)..."), "HIVTestHandler"));
    database->addAction(d->guiFactory->createAction(tr("产品信息配置(&P)..."), "HProductEditHandler"));
    database->addAction(d->guiFactory->createAction(tr("数据库浏览(&B)..."), "HSqlBrowserHandler"));
    account->addAction(d->guiFactory->createAction(tr("管理员登入(&I)..."), "HLoginInHandler"));
    account->addAction(d->guiFactory->createAction(tr("注销(&O)..."), "HLoginOutHandler"));
    d->mainWindow->insertMenu(calibrate);
    d->mainWindow->insertMenu(grade);
    d->mainWindow->insertMenu(adjust);
    d->mainWindow->insertMenu(quality);
    d->mainWindow->insertMenu(test);
    d->mainWindow->insertMenu(database);
    d->mainWindow->insertMenu(account);
    d->mainWindow->setAuthority(0);
}

void HBuilder2100DC::buildTestWidget()
{
    ITestWidget *widget = new HTestWidget2100DC;
    HAppContext::setContextPointer("ITestWidget", widget);
}
