#include "HBuilder2000DC_p.h"
#include "HTestWidget2000DC.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IDataFactory.h"
#include "HeData/IFileStream.h"
#include "HeData/ISpecCalibrateCollection.h"
#include "HeData/ISpecCalibrate.h"
#include "HeData/IElecCalibrateCollection.h"
#include "HeData/IElecCalibrate.h"
#include "HeData/IChromatismCollection.h"
#include "HeData/ITestSpec.h"
#include "HeData/ITestElec.h"
#include "HeCommunicate/ICommunicateFactory.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IDeviceCollection.h"
#include "HeCommunicate/IDevice.h"
#include "HeController/IControllerFactory.h"
#include "HeController/IThreadCollection.h"
#include "HeGui/IGuiFactory.h"
#include "HeGui/IMainWindow.h"
#include "HeGui/HAction.h"
#include <QtWidgets/QMenu>
#include <QtCore/QDebug>

HBuilder2000DC::HBuilder2000DC(IMainWindow *parent) :
    HAbstractBuilder(*new HBuilder2000DCPrivate(parent), parent)
{
    Q_D(HBuilder2000DC);
    d->sqlField = QStringList() << "ID" << "Manufacturer" << "ProductName" << "ProductModel" << "SampleNumber" << "Tester" << "TestInstitute"
                                << "Temperature" << "Humidity" << "TestDate" << "TestTime"
                                << "OutputVoltage" << "OutputCurrent" << "MeasuredVoltage" << "MeasuredCurrent" << "ReverseVoltage" << "ReverseCurrent" << "ElecPower"
                                << "LuminousFluxSpec" << "LuminousPower" << "LuminousEfficiency"
                                << "PeakWave" << "PeakBandwidth" << "DominantWave"
                                << "ColorTemperature" << "ColorPurity"
                                << "CC_x" << "CC_y" << "CC_up" << "CC_vp" << "Duv"
                                << "RedRatio" << "GreenRadio" << "BlueRatio"
                                << "Ra" << "Rx" << "EnergyGraph";
    HAppContext::setContextValue("GradeOptionals",      QStringList() << "[实测电压]" << "[实测电流]" << "[反向漏流]" << "[电功率]" << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数]" << "[色坐标]");
    HAppContext::setContextValue("QualityOptionals",    QStringList() << "[实测电压]" << "[实测电流]" << "[反向漏流]" << "[电功率]" << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数]" << "[色坐标x]" << "[色坐标y]");
    HAppContext::setContextValue("AdjustOptionals",     QStringList() << "[光谱光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数]" << "[色坐标x]" << "[色坐标y]");
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
            auto fit = d->dataFactory->createSpecFitting("HSpecFittingPolynom");
            auto spec = d->dataFactory->createSpecCalibrate("HSpecCalibrate");
            spec->setFitting(fit);
            specs->insert("1", spec);
        }

        QVariantMap param[6];
        param[0].insert("itemClassName", "HElecCalibrateItem");
        param[0].insert("itemTypeList", QStringList() << "[输出电压]");
        param[1].insert("itemClassName", "HElecCalibrateItem");
        param[1].insert("itemTypeList", QStringList() << "[输出电流]");
        param[2].insert("itemClassName", "HElecCalibrateItem");
        param[2].insert("itemTypeList", QStringList() << "[实测电压]");
        param[3].insert("itemClassName", "HElecCalibrateItem");
        param[3].insert("itemTypeList", QStringList() << "[实测电流]");
        param[4].insert("itemClassName", "HElecCalibrateItem");
        param[4].insert("itemTypeList", QStringList() << "[反向电压]");
        param[5].insert("itemClassName", "HElecCalibrateItem");
        param[5].insert("itemTypeList", QStringList() << "[反向漏流]");
        auto elec = d->dataFactory->createElecCalibrate("HElecCalibrate");
        elec->setItemCollection(OutputVoltage,   d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[0]));
        elec->setItemCollection(OutputCurrent,   d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[1]));
        elec->setItemCollection(MeasuredVoltage, d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[2]));
        elec->setItemCollection(MeasuredCurrent, d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[3]));
        elec->setItemCollection(ReverseVoltage,  d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[4]));
        elec->setItemCollection(ReverseCurrent,  d->dataFactory->createElecCalibrateItemCollection("HElecCalibrateItemCollection", param[5]));
        auto elecs = d->dataFactory->createElecCalibrateCollection("HElecCalibrateCollection");
        elecs->insert("1", elec);

        auto chromatisms = d->dataFactory->createChromatismCollection("HChromatismCollection");
        chromatisms->fileStream()->readFile(":/dat/Chromatism.hcc");
        d->configManage->setContain(IConfigManage::ContainSpec
                                    | IConfigManage::ContainElec
                                    | IConfigManage::ContainChromatism
                                    | IConfigManage::ContainGrade
                                    | IConfigManage::ContainAdjust
                                    | IConfigManage::ContainQuality);
        d->configManage->setSpecCalibrateCollection(specs);
        d->configManage->setElecCalibrateCollection(elecs);
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
    elec->setSuccessor(other);
    elec->setCalibrate(d->configManage->elecCalibrateCollection());
    spec->setSuccessor(elec);
    spec->setCalibrate(d->configManage->specCalibrate("1"));
    data->setSuccessor(spec);
    HAppContext::setContextPointer("ITestData", data);
    HAppContext::setContextPointer("ITestOther", other);
    HAppContext::setContextPointer("ITestSpec", spec);
    HAppContext::setContextPointer("ITestElec", elec);
}

void HBuilder2000DC::buildDevice()
{
    Q_D(HBuilder2000DC);
    QVariantMap param[2];
    param[0].insert("timeOut", 3000);
    param[1].insert("timeOut", 3000);
    param[1].insert("baudRate", 115200);
    auto port1 = d->communicateFactory->createPort("HUsbPortCy", param[0]);
    auto port2 = d->communicateFactory->createPort("HSerialPort", param[1]);
    auto device1 = d->communicateFactory->createDevice("HSlDevice2");
    auto device2 = d->communicateFactory->createDevice("HSlCodecDevice");
    auto devices = d->communicateFactory->createDeviceCollection("HDeviceCollection");
    auto protocol1 = d->communicateFactory->createProtocol("HBigProtocol");
    auto protocol2 = d->communicateFactory->createProtocol("HLittleProtocol");
    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
    device1->setPort(port1, 0, false);
    device1->addActionParam(ACT_CHECK_DEVICE,       QList<uchar>() << 0x00 << 0x02 << 0x00);
    device1->addActionParam(ACT_SET_INTEGRAL_TIME,  QList<uchar>() << 0x00 << 0x04 << 0x01);
    device1->addActionParam(ACT_GET_SPECTRUM,       QList<uchar>() << 0x10 << 0x50 << 0x02);
    device1->addActionParam(ACT_SET_RAM,            QList<uchar>() << 0xFF << 0xFA << 0x03);
    device1->addActionParam(ACT_GET_RAM,            QList<uchar>() << 0xFF << 0xFA << 0x04);
    device2->setPort(port2, 4, true);
    device2->setDeviceID(0x01);
    device2->addActionParam(ACT_CHECK_DEVICE,               QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x00);
    device2->addActionParam(ACT_SET_SOURCE_MODE,            QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x05);
    device2->addActionParam(ACT_SET_OUTPUT_VOLTAGE,         QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x06);
    device2->addActionParam(ACT_SET_OUTPUT_CURRENT,         QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x07);
    device2->addActionParam(ACT_SET_GEARS_OUTPUT_CURRENT,   QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x08);
    device2->addActionParam(ACT_SET_REVERSE_VOLTAGE,        QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x09);
    device2->addActionParam(ACT_GET_ELEC_PARAM,             QList<uchar>() << 0x00 << 0x06 << 0x01 << 0x11);
    device2->addActionParam(ACT_GET_MEASURED_VOLTAGE,       QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x12);
    device2->addActionParam(ACT_GET_MEASURED_CURRENT,       QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x13);
    device2->addActionParam(ACT_GET_REVERSE_CURRENT,        QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x14);
    devices->insert("Spec", device1);
    devices->insert("Elec", device2);
    protocol1->setDevice(device1);
    protocol2->setDevice(device2);
    protocols->insert("Spec", protocol1);
    protocols->insert("Elec", protocol2);
    HAppContext::setContextPointer("IProtocolCollection", protocols);
}

void HBuilder2000DC::buildThread()
{
    Q_D(HBuilder2000DC);
    auto thread = d->controllerFactory->createThread("HSpecElecThread");
    auto threads = d->controllerFactory->createThreadCollection("HThreadCollection");
    threads->insert("1", thread);
    HAppContext::setContextPointer("IThreadCollection", threads);
}

void HBuilder2000DC::buildModel()
{
    Q_D(HBuilder2000DC);
    d->model = d->controllerFactory->createModel("HSpecElecModel");
    HAppContext::setContextPointer("IModel", d->model);
}

void HBuilder2000DC::buildDatabase()
{

}

void HBuilder2000DC::buildMenu()
{
    Q_D(HBuilder2000DC);
    auto calibrate = new QMenu(tr("定标(&C)"));
    auto grade = new QMenu(tr("分级(&G)"));
    auto adjust = new QMenu(tr("调整(&A)"));
    auto quality = new QMenu(tr("品质(&Q)"));
    auto database = new QMenu(tr("数据库(&D)"));
    calibrate->addAction(d->guiFactory->createAction(tr("光谱定标(&S)..."), "HSpecCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("电定标(&S)..."), "HElecCalibrateHandler"));
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

void HBuilder2000DC::buildTestWidget()
{
    ITestWidget *widget = new HTestWidget2000DC;
    widget->setVisible(false);
    HAppContext::setContextPointer("ITestWidget", widget);
}
