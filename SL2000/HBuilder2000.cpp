#include "HBuilder2000_p.h"
#include "HTestWidget2000.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/ICommunicateFactory.h"
#include "HeCommunicate/IDevice.h"
#include "HeCommunicate/IDeviceCollection.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeController/IControllerFactory.h"
#include "HeController/IThreadCollection.h"
#include "HeData/IConfigManage.h"
#include "HeData/IDataFactory.h"
#include "HeData/IFileStream.h"
#include "HeData/ITestSpec.h"
#include "HeData/ISpecCalibrateCollection.h"
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
#include <QtWidgets/QMenu>
#include <QtCore/QDebug>


HBuilder2000::HBuilder2000(IMainWindow *parent) :
    HAbstractBuilder(*new HBuilder2000Private(parent), parent)
{
    Q_D(HBuilder2000);
    d->configFileName = "SL2000.cfg";
    HAppContext::setContextValue("Settings", "Ini\\SL2000.ini");
    HAppContext::setContextValue("ConfigFileName", d->configFileName);
    HAppContext::setContextValue("GradeOptionals",      QStringList() << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数]" << "[色坐标]");
    HAppContext::setContextValue("AdjustOptionals",     QStringList() << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数]" << "[色坐标x]" << "[色坐标y]");
    HAppContext::setContextValue("QualityOptionals",    QStringList() << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数]" << "[色坐标x]" << "[色坐标y]");
}

HBuilder2000::~HBuilder2000()
{
    qDebug() << __func__;
}

void HBuilder2000::initialize(QVariantMap /*param*/)
{
}

QString HBuilder2000::typeName()
{
    return "HBuilder2000";
}

void HBuilder2000::buildConfigManage()
{
    Q_D(HBuilder2000);
    d->configManage = d->dataFactory->createConfigManage("HConfigManage");
    if (!d->configManage->fileStream()->readFile(d->configFileName))
    {
        auto specs = d->dataFactory->createSpecCalibrateCollection("HSpecCalibrateCollection");
        if (!specs->fileStream()->readFile(":/Dat/Spectrum.hcs"))
        {
            auto spec = d->dataFactory->createSpecCalibrate("HSpecCalibrate");
            specs->insert("1", spec);
        }
        d->configManage->setContain(IConfigManage::ContainSpec | IConfigManage::ContainGrade | IConfigManage::ContainAdjust | IConfigManage::ContainQuality);
        d->configManage->setSpecCalibrateCollection(specs);
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
    auto other = d->dataFactory->createTestData("HTestData");
    auto spec = d->dataFactory->createTestSpec("HTestSpec");
    spec->setSuccessor(other);
    spec->setCalibrate(d->configManage->specCalibrate("1"));
    data->setSuccessor(spec);
    HAppContext::setContextPointer("ITestData", data);
    HAppContext::setContextPointer("ITestOther", other);
    HAppContext::setContextPointer("ITestSpec", spec);
}

void HBuilder2000::buildDevice()
{
    Q_D(HBuilder2000);
    QVariantMap param;
    param.insert("timeOut", 1000);
    auto port = d->communicateFactory->createPort("HUsbPortCy", param);
    auto device = d->communicateFactory->createDevice("HSlDevice");
    auto devices = d->communicateFactory->createDeviceCollection("HDeviceCollection");
    auto protocol = d->communicateFactory->createProtocol("HProtocol");
    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
    device->setPort(port, 0, false);
    device->setDeviceID(0x81);
    device->addActionParam(ACT_CHECK_DEVICE,        QList<uchar>() << 0x00 << 0x02 << 0x03 << 0x00);
    device->addActionParam(ACT_SET_INTEGRAL_TIME,   QList<uchar>() << 0x00 << 0x04 << 0x03 << 0x05);
    device->addActionParam(ACT_GET_SPECTRUM,        QList<uchar>() << 0x12 << 0x00 << 0x03 << 0x11);
    devices->insert("Spec", device);
//    devices->addSupport(ACT_PULSE_TEST);
//    devices->addSupport(ACT_GET_LUMINOUS_SPECTRUM);
//    devices->addSupport(ACT_GET_ELEC_LUMINOUS_SPECTRUM);
    protocol->setDevice(device);
    protocols->insert("Spec", protocol);
    HAppContext::setContextPointer("IDeviceCollection", devices);
    HAppContext::setContextPointer("IProtocolCollection", protocols);
}

void HBuilder2000::buildThread()
{
    Q_D(HBuilder2000);
    auto thread = d->controllerFactory->createThread("HSpecThread");
    auto threads = d->controllerFactory->createThreadCollection("HThreadCollection");
    threads->insert("Spec", thread);
    HAppContext::setContextPointer("IThreadCollection", threads);
}

void HBuilder2000::buildModel()
{
    Q_D(HBuilder2000);
    d->model = d->controllerFactory->createModel("HSpecModel");
    HAppContext::setContextPointer("IModel", d->model);
}

void HBuilder2000::buildDatabase()
{
    Q_D(HBuilder2000);
    auto field = QStringList() << "ID" << "Manufacturer" << "ProductName" << "ProductModel" << "SampleNumber" << "Tester" << "TestInstitute"
                               << "Temperature" << "Humidity" << "TestDate" << "TestTime"
                               << "LuminousFluxSpec" << "LuminousPower"
                               << "PeakWave" << "PeakBandwidth" << "DominantWave"
                               << "ColorTemperature" << "ColorPurity"
                               << "CC_x" << "CC_y" << "CC_up" << "CC_vp" << "Duv"
                               << "RedRatio" << "GreenRadio" << "BlueRatio"
                               << "Ra" << "Rx" << "EnergyGraph";
    auto find = field;
    auto exportExcel = field;
    find.removeFirst();
    find.removeLast();
    find.removeLast();
    exportExcel.removeLast();

    auto db = d->sqlFactory->createDatabase("HSqlDatabase");
    auto model = d->sqlFactory->createTableModel("HSqlTableModel");
    auto info = d->sqlFactory->createProductInfo("HProductInfo");
    auto handle = d->sqlFactory->createHandle("HSqlHandle");
    auto print = d->sqlFactory->createPrint("HSpecSqlPrint");
    auto browser = d->sqlFactory->createBrowser("HSqlBrowser", d->mainWindow);
    db->openDatabase("SL2000.db");
    model->setField(field);
    model->setTable("Spec");
    info->setRelationTableName("Spec");
    handle->setProductInfo(info);
    handle->setFieldFind(find);
    print->setFieldExportExcel(exportExcel);
    browser->setRecordHandle(handle);
    browser->setRecordPrint(print);
    browser->setModel(model);
    db->insertTableModel("Spec", model);
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
    auto database = new QMenu(tr("数据库(&D)"));
    calibrate->addAction(d->guiFactory->createAction(tr("光谱定标(&S)..."), "HSpecCalibrateHandler"));
    grade->addAction(d->guiFactory->createAction(tr("分级数据配置(&E)..."), "HGradeEditHandler"));
    grade->addAction(d->guiFactory->createAction(tr("分级数据选择(&S)..."), "HGradeSelectHandler"));
    adjust->addAction(d->guiFactory->createAction(tr("调整数据配置(&E)..."), "HAdjustEditHandler"));
    adjust->addAction(d->guiFactory->createAction(tr("调整数据选择(&S)..."), "HAdjustSelectHandler"));
    quality->addAction(d->guiFactory->createAction(tr("品质数据配置(&E)..."), "HQualityEditHandler"));
    quality->addAction(d->guiFactory->createAction(tr("品质数据选择(&S)..."), "HQualitySelectHandler"));
    database->addAction(d->guiFactory->createAction(tr("产品信息配置(&P)..."), "HProductInfoEditHandler"));
    database->addAction(d->guiFactory->createAction(tr("数据库浏览(&B)..."), "HSqlBrowserHandler"));
    d->mainWindow->insertMenu(calibrate);
    d->mainWindow->insertMenu(grade);
    d->mainWindow->insertMenu(adjust);
    d->mainWindow->insertMenu(quality);
    d->mainWindow->insertMenu(database);
}

void HBuilder2000::buildTestWidget()
{
    ITestWidget *widget = new HTestWidget2000;
    widget->setVisible(false);
    HAppContext::setContextPointer("ITestWidget", widget);
}

//void HBuilder2000::buildProtocol()
//{
//    Q_D(HBuilder2000);
//    QVariantMap param;
//    param.insert("device", ToVariant(d->devices->value("Spec")));
//    auto protocol = d->communicateFactory->createProtocol("HProtocol", param);
//    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
//    protocols->insert("Spec", protocol);
//    HAppContext::setContextPointer("IProtocolCollection", protocols);
//}
