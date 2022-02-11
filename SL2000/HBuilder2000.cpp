#include "HBuilder2000_p.h"
#include "HTestWidget2000.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IDataFactory.h"
#include "HeData/IDataStream.h"
#include "HeData/ISpecCalibrateCollection.h"
#include "HeData/ISpecCalibrate.h"
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

HBuilder2000Private::HBuilder2000Private()
{
    deploy.insert("SpecFitting",    "HSpecFittingPolynom"); // HSpecFittingPolynom: 多项式拟合; HSpecFittingLinear : 插值拟合
    deploy.insert("CcdProtocol",    "HCcdProtocol01");      // HCcdProtocol01:1305; HCcdProtocol02:554b

    auto list = QStringList() << "|产品信息2|" << "|环境信息|" << "|时间信息2|" << "|光度信息3|" << "|光谱信息2|" << "|色容差信息2|" << "|光合信息|" << "|TM30信息|";
    sqlField = QStringList() << "ID" << HSql::membership(list);
//    sqlField = QStringList() << "ID" << "Manufacturer" << "ProductName" << "ProductModel" << "SampleNumber" << "Tester" << "TestInstitute"
//                             << "Temperature" << "Humidity" << "TestDate" << "TestTime"
//                             << "LuminousFluxSpec" << "LuminousPower"
//                             << "PeakWave" << "PeakBandwidth" << "DominantWave"
//                             << "ColorTemperature" << "ColorPurity"
//                             << "CC_x" << "CC_y" << "CC_up" << "CC_vp" << "Duv"
//                             << "RedRatio" << "GreenRadio" << "BlueRatio"
//                             << "Ra" << "R9" << "Rx"
//                             << "EnergyGraph" << "ReflectGraph"
//                             << "TM30_Rf" << "TM30_Rg" << "TM30_Rfi"
//                             << "TM30_hj_Rf" << "TM30_hj_Rcs" << "TM30_hj_Rhs"
//                             << "TM30_hj_at" << "TM30_hj_bt" << "TM30_hj_ar" << "TM30_hj_br"
//                             << "TM30_hj_atn" << "TM30_hj_btn" << "TM30_hj_arn" << "TM30_hj_brn";
    HAppContext::setContextValue("GradeOptionals",      QStringList() << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标]");
    HAppContext::setContextValue("AdjustOptionals",     QStringList() << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标x]" << "[色坐标y]");
    HAppContext::setContextValue("QualityOptionals",    QStringList() << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标x]" << "[色坐标y]");
}

HBuilder2000::HBuilder2000(QObject *parent) :
    HAbstractBuilder(*new HBuilder2000Private, parent)
{
}

HBuilder2000::~HBuilder2000() = default;

QString HBuilder2000::typeName()
{
    return "HBuilder2000";
}

void HBuilder2000::buildConfigManage()
{
    Q_D(HBuilder2000);
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

void HBuilder2000::buildTestData()
{
    Q_D(HBuilder2000);
    auto data = d->dataFactory->createTestData("HTestData");
    auto product = d->dataFactory->createTestData("HTestProduct");
    auto spec = d->dataFactory->createTestSpec("HTestSpec");
    spec->setCalibrate(d->configManage->specCalibrate("1"));
    data->setSuccessor(product)->setSuccessor(spec);
    HAppContext::setContextPointer("ITestData", data);
    HAppContext::setContextPointer("ITestProduct", product);
    HAppContext::setContextPointer("ITestSpec", spec);
}

void HBuilder2000::buildTemplate()
{
    Q_D(HBuilder2000);
    auto expor = d->dataFactory->createTextExport("HTextExport");
    auto text = d->guiFactory->createTextExportTemplate("HSpecTextExportTemplate");
    auto print = d->dataFactory->createPrint("HPrint");
    auto spec = d->guiFactory->createPrintTemplate("HSpecPrintTemplate");
    HAppContext::setContextPointer("ITextExport", expor);
    HAppContext::setContextPointer("ISpecTextExportTemplate", text);
    HAppContext::setContextPointer("IPrint", print);
    HAppContext::setContextPointer("ISpecPrintTemplate", spec);
}

void HBuilder2000::buildDevice()
{
    Q_D(HBuilder2000);
#ifdef SIMULATE // 模拟设备
    auto device = d->communicateFactory->createDevice("HSpecSimulateDevice");
    auto protocol = d->communicateFactory->createProtocol("HLittleProtocol");
    protocol->setDevice(device);
#else
    auto protocol = d->communicateFactory->createProtocol(deployItem("CcdProtocol"));
#endif
    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
    protocols->insert("Spec", protocol);
    HAppContext::setContextPointer("IProtocolCollection", protocols);
}

void HBuilder2000::buildThread()
{
    Q_D(HBuilder2000);
    auto thread = d->controllerFactory->createThread("HSpecThread");
    auto threads = d->controllerFactory->createThreadCollection("HThreadCollection");
    threads->insert("1", thread);
    HAppContext::setContextPointer("IThreadCollection", threads);
}

void HBuilder2000::buildModel()
{
    Q_D(HBuilder2000);
    auto model = d->controllerFactory->createModel("HSpecModel");
    HAppContext::setContextPointer("IModel", model);
}

void HBuilder2000::buildMemento()
{
    Q_D(HBuilder2000);
    auto mementos = d->controllerFactory->createMementoCollection("HMementoCollection");
    if (!mementos->readFile(QString("%1.tmp").arg(QApplication::applicationName())) || !mementos->contains("Spec"))
    {
        auto memento = d->controllerFactory->createMemento("HMemento");
        memento->setDataType(QStringList() << "[积分时间]");
        mementos->insert("Spec", memento);
    }
    HAppContext::setContextPointer("IMementoCollection", mementos);
}

void HBuilder2000::buildDatabase()
{
    Q_D(HBuilder2000);
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
        // 1.1.1.2 添加列R9
        if (version < 0x01010102)
            HSqlHelper::addColumn("Spec", "R9");
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

void HBuilder2000::buildMenu()
{
    Q_D(HBuilder2000);
    auto calibrate = new QMenu(tr("定标(&C)"));
    auto grade = new QMenu(tr("分级(&G)"));
    auto adjust = new QMenu(tr("调整(&A)"));
    auto quality = new QMenu(tr("品质(&Q)"));
    auto device = new QMenu(tr("设备配置(&T)"));
    auto database = new QMenu(tr("数据库(&D)"));
    calibrate->addAction(d->guiFactory->createAction(tr("光谱定标(&S)..."), "HSpecCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("光通量自吸收配置(&S)..."), "HSpecLuminousHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("色温配置(&T)..."), "HSpecTcHandler"));
    grade->addAction(d->guiFactory->createAction(tr("分级数据配置(&E)..."), "HGradeEditHandler"));
    grade->addAction(d->guiFactory->createAction(tr("分级数据选择(&S)..."), "HGradeSelectHandler"));
    adjust->addAction(d->guiFactory->createAction(tr("调整数据配置(&E)..."), "HAdjustEditHandler"));
    adjust->addAction(d->guiFactory->createAction(tr("调整数据选择(&S)..."), "HAdjustSelectHandler"));
    quality->addAction(d->guiFactory->createAction(tr("品质数据配置(&E)..."), "HQualityEditHandler"));
    quality->addAction(d->guiFactory->createAction(tr("品质数据选择(&S)..."), "HQualitySelectHandler"));
    device->addAction(d->guiFactory->createAction(tr("从设备读取数据(&G)..."), "HImportDeviceHandler"));
    device->addAction(d->guiFactory->createAction(tr("写入数据到设备(&S)..."), "HExportDeviceHandler"));
    device->addAction(d->guiFactory->createAction(tr("导入标准曲线(&I)..."), "HImportCurveHandler"));
    device->addAction(d->guiFactory->createAction(tr("导出标准曲线(&E)..."), "HExportCurveHandler"));
    database->addAction(d->guiFactory->createAction(tr("产品信息配置(&P)..."), "HProductEditHandler"));
    database->addAction(d->guiFactory->createAction(tr("数据库浏览(&B)..."), "HSqlBrowserHandler"));
    d->mainWindow->insertMenu(calibrate);
    d->mainWindow->insertMenu(grade);
    d->mainWindow->insertMenu(adjust);
    d->mainWindow->insertMenu(quality);
    d->mainWindow->insertMenu(device);
    d->mainWindow->insertMenu(database);
}

void HBuilder2000::buildTestWidget()
{
    ITestWidget *widget = new HTestWidget2000;
    HAppContext::setContextPointer("ITestWidget", widget);
}
