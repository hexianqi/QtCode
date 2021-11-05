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

HBuilder2000Private::HBuilder2000Private()
{
    deploy.insert("SpecFitting",    "HSpecFittingPolynom"); // HSpecFittingPolynom: 多项式拟合; HSpecFittingLinear : 插值拟合
    deploy.insert("CcdProtocol",    "HCcdProtocol01");      // HCcdProtocol01:1305; HCcdProtocol02:554b

    sqlField = QStringList() << "ID" << "Manufacturer" << "ProductName" << "ProductModel" << "SampleNumber" << "Tester" << "TestInstitute"
                             << "Temperature" << "Humidity" << "TestDate" << "TestTime"
                             << "LuminousFluxSpec" << "LuminousPower"
                             << "PeakWave" << "PeakBandwidth" << "DominantWave"
                             << "ColorTemperature" << "ColorPurity"
                             << "CC_x" << "CC_y" << "CC_up" << "CC_vp" << "Duv"
                             << "RedRatio" << "GreenRadio" << "BlueRatio"
                             << "Ra" << "R9" << "Rx" << "EnergyGraph";
    HAppContext::setContextValue("GradeOptionals",      QStringList() << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标]");
    HAppContext::setContextValue("AdjustOptionals",     QStringList() << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标x]" << "[色坐标y]");
    HAppContext::setContextValue("QualityOptionals",    QStringList() << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标x]" << "[色坐标y]");
}

HBuilder2000::HBuilder2000(QObject *parent) :
    HAbstractBuilder(*new HBuilder2000Private, parent)
{
}

HBuilder2000::~HBuilder2000()
{
    qDebug() << __func__;
}

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

    auto print = d->dataFactory->createPrint("HPrint");
    auto expor = d->dataFactory->createTextExport("HTextExport");
    auto spec = d->guiFactory->createPrintTemplate("HSpecPrintTemplate");
    auto text = d->guiFactory->createTextExportTemplate("HSpecTextExportTemplate");
    HAppContext::setContextPointer("IPrint", print);
    HAppContext::setContextPointer("ITextExport", expor);
    HAppContext::setContextPointer("ISpecPrintTemplate", spec);
    HAppContext::setContextPointer("ISpecTextExportTemplate", text);
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
    auto memento = d->controllerFactory->createMemento("HMemento");
    memento->setDataTypes(QStringList() << "[积分时间]");
    memento->readFile(QString("%1.tmp").arg(QApplication::applicationName()));
    HAppContext::setContextPointer("IMementoTest", memento);
}

void HBuilder2000::buildDatabase()
{
    Q_D(HBuilder2000);
    auto find = d->sqlField;
    auto exportExcel = d->sqlField;
    find.removeFirst();
    find.removeLast();
    find.removeLast();
    exportExcel.removeLast();

    auto db = d->sqlFactory->createDatabase("HSqlDatabase");
    db->openDatabase(QString("%1.db").arg(QApplication::applicationName()));
    HSqlHelper::setVersion("Spec", 0x01010101);

    auto model = d->sqlFactory->createTableModel("HSqlTableModel");
    auto info = d->sqlFactory->createProductInfo("HProductInfo");
    auto handle = d->sqlFactory->createHandle("HSqlHandle");
    auto print = d->sqlFactory->createPrint("HSpecSqlPrint");
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

//void HBuilder2000::buildProtocol()
//{
//    Q_D(HBuilder2000);
//    QVariantMap param;
//    param.insert("device", ToVariant(d->devices->value("Spec")));
//    auto protocol = d->communicateFactory->createProtocol("HLittleProtocol", param);
//    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
//    protocols->insert("Spec", protocol);
//    HAppContext::setContextPointer("IProtocolCollection", protocols);
//}

//// 第一版设备554b
//void HBuilder2000::buildDevice()
//{
//    Q_D(HBuilder2000);
//    QVariantMap param;
//    param.insert("timeOut", 1000);
//    auto port = d->communicateFactory->createPort("HUsbPortCy", param);
//    auto device = d->communicateFactory->createDevice("HSlDevice1");
//    auto devices = d->communicateFactory->createDeviceCollection("HDeviceCollection");
//    auto protocol = d->communicateFactory->createProtocol("HLittleProtocol");
//    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
//    device->setPort(port, 0, false);
//    device->setDeviceID(0x81);
//    device->addActionParam(ACT_CHECK_DEVICE,        QList<uchar>() << 0x00 << 0x02 << 0x03 << 0x00);
//    device->addActionParam(ACT_SET_INTEGRAL_TIME,   QList<uchar>() << 0x00 << 0x04 << 0x03 << 0x05);
//    device->addActionParam(ACT_GET_SPECTRUM,        QList<uchar>() << 0x12 << 0x00 << 0x03 << 0x11);
//    devices->insert("Spec", device);
////    devices->addSupport(ACT_PULSE_TEST);
////    devices->addSupport(ACT_GET_LUMINOUS_SPECTRUM);
////    devices->addSupport(ACT_GET_ELEC_LUMINOUS_SPECTRUM);
//    protocol->setDevice(device);
//    protocols->insert("Spec", protocol);
//    HAppContext::setContextPointer("IDeviceCollection", devices);
//    HAppContext::setContextPointer("IProtocolCollection", protocols);
//}

// 第二版设备1305
//void HBuilder2000::buildDevice()
//{
//    Q_D(HBuilder2000);
//    QVariantMap param;
//    param.insert("timeOut", 3000);
//    auto port = d->communicateFactory->createPort("HUsbPortCy", param);
//    auto device = d->communicateFactory->createDevice("HSlDevice2");
//    auto devices = d->communicateFactory->createDeviceCollection("HDeviceCollection");
//    auto protocol = d->communicateFactory->createProtocol("HBigProtocol");
//    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
//    device->setPort(port, 0, false);
//    device->addActionParam(ACT_CHECK_DEVICE,        QList<uchar>() << 0x00 << 0x02 << 0x00);
//    device->addActionParam(ACT_SET_INTEGRAL_TIME,   QList<uchar>() << 0x00 << 0x04 << 0x01);
//    device->addActionParam(ACT_GET_SPECTRUM,        QList<uchar>() << 0x10 << 0x50 << 0x02);
//    device->addActionParam(ACT_SET_RAM,             QList<uchar>() << 0xFF << 0xFA << 0x03);
//    device->addActionParam(ACT_GET_RAM,             QList<uchar>() << 0xFF << 0xFA << 0x04);
//    devices->insert("Spec", device);
//    protocol->setDevice(device);
//    protocols->insert("Spec", protocol);
//    HAppContext::setContextPointer("IProtocolCollection", protocols);
//}

//// 设备模拟
//void HBuilder2000::buildDevice()
//{
//    Q_D(HBuilder2000);
//    auto device = d->communicateFactory->createDevice("HSpecSimulateDevice");
//    auto protocol = d->communicateFactory->createProtocol("HLittleProtocol");
//    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
//    protocol->setDevice(device);
//    protocols->insert("Spec", protocol);
//    HAppContext::setContextPointer("IProtocolCollection", protocols);
//}
