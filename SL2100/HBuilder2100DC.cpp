#include "HBuilder2100DC_p.h"
#include "HThread2100DC.h"
#include "HModel2100DC.h"
#include "HSqlPrint2100DC.h"
#include "HTestWidget2100DC.h"
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
                             << "Ra" << "R9" << "Rx" << "EnergyGraph";
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

HBuilder2100DC::~HBuilder2100DC()
{
    qDebug() << __func__;
}

void HBuilder2100DC::initialize(QVariantMap /*param*/)
{

}

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
    auto other = d->dataFactory->createTestData("HTestData");
    auto spec = d->dataFactory->createTestSpec("HTestSpec");
    spec->setSuccessor(other);
    spec->setCalibrate(d->configManage->specCalibrate("1"));
    data->setSuccessor(spec);
    HAppContext::setContextPointer("ITestData", data);
    HAppContext::setContextPointer("ITestOther", other);
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
    auto protocol2 = d->communicateFactory->createProtocol("HDaXinProtocol");
#endif
    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
    protocols->insert("Spec", protocol1);
    protocols->insert("Elec", protocol2);
    HAppContext::setContextPointer("IProtocolCollection", protocols);
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
    Q_D(HBuilder2100DC);
    d->model = new HModel2100DC(this);
    HAppContext::setContextPointer("IModel", d->model);
}

void HBuilder2100DC::buildMemento()
{
    Q_D(HBuilder2100DC);
    auto memento = d->controllerFactory->createMemento("HMemento");
    memento->setItems(QStringList() << "[积分时间]" << "[输出电压]" << "[输出电流]");
    memento->readFile(QString("%1.tmp").arg(QApplication::applicationName()));
    HAppContext::setContextPointer("IMementoTest", memento);
}

void HBuilder2100DC::buildDatabase()
{
    Q_D(HBuilder2100DC);
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
    auto print = new HSqlPrint2100DC(this);
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

void HBuilder2100DC::buildMenu()
{
    Q_D(HBuilder2100DC);
    auto calibrate = new QMenu(tr("定标(&C)"));
    auto grade = new QMenu(tr("分级(&G)"));
    auto adjust = new QMenu(tr("调整(&A)"));
    auto quality = new QMenu(tr("品质(&Q)"));
    auto test = new QMenu(tr("其他测试(&E)"));
    auto database = new QMenu(tr("数据库(&D)"));
    calibrate->addAction(d->guiFactory->createAction(tr("光谱定标(&S)..."), "HSpecCalibrateHandler"));
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

void HBuilder2100DC::buildTestWidget()
{
    ITestWidget *widget = new HTestWidget2100DC;
    HAppContext::setContextPointer("ITestWidget", widget);
}
