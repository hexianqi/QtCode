#include "HBuilder7000_p.h"
#include "HKeyenceProtocol.h"
#include "HThread7000.h"
#include "HModel7000.h"
#include "HTestWidget7000.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IDataFactory.h"
#include "HeData/IDataStream.h"
#include "HeData/ISpecCalibrate.h"
#include "HeData/ISpecCalibrateCollection.h"
#include "HeData/IChromatismCollection.h"
#include "HeData/ILuminousCalibrate.h"
#include "HeData/ILuminousCalibrateItem.h"
#include "HeData/ILuminousCalibrateCollection.h"
#include "HeData/IElecCalibrate.h"
#include "HeData/IElecCalibrateCollection.h"
#include "HeData/ITestSpec.h"
#include "HeCommunicate/ICommunicateFactory.h"
#include "HeCommunicate/IProtocol.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeController/IControllerFactory.h"
#include "HeController/IThreadCollection.h"
#include "HeController/IMemento.h"
#include "HeController/IMementoCollection.h"
#include "HeSql/HSql.h"
#include "HeGui/IGuiFactory.h"
#include "HeGui/IMainWindow.h"
#include "HeGui/HAction.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>

HBuilder7000Private::HBuilder7000Private()
{
    deploy.insert("CcdProtocol",    "HCcdProtocol01");      // HCcdProtocol01:1305; HCcdProtocol02:554b
    HAppContext::setContextValue("SpecCalibrateSetWidgetType",  "HSpecCalibrateSetWidget2");
    HAppContext::setContextValue("AdjustSetWidgetType",         "HAdjustSetWidget2");
    HAppContext::setContextValue("GradeOptional",               QStringList() << "[实测电压]" << "[实测电流]" << "[反向漏流]" << "[电功率]" << "[光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标]");
    HAppContext::setContextValue("QualityOptional",             QStringList() << "[实测电压]" << "[实测电流]" << "[反向漏流]" << "[电功率]" << "[光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[色坐标x]" << "[色坐标y]");
    HAppContext::setContextValue("AdjustOptional",              QStringList() << "[实测电压]" << "[实测电流]" << "[光通量]" << "[峰值波长]" << "[主波长]" << "[色纯度]" << "[色温]" << "[显色指数Ra]" << "[显色指数R9]" << "[色坐标x]" << "[色坐标y]");
}

HBuilder7000::HBuilder7000(QObject *parent) :
    HAbstractBuilder(*new HBuilder7000Private, parent)
{
}

HBuilder7000::HBuilder7000(HBuilder7000Private &p, QObject *parent) :
    HAbstractBuilder(p, parent)
{
}

HBuilder7000::~HBuilder7000() = default;

QString HBuilder7000::typeName()
{
    return "HBuilder7000";
}

void HBuilder7000::buildConfigManage()
{
    Q_D(HBuilder7000);
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

        auto luminousItem1 = d->dataFactory->createLuminousCalibrateItem("HLuminousCalibrateItem");
        auto luminousItem2 = d->dataFactory->createLuminousCalibrateItem("HLuminousCalibrateItem");
        auto luminous = d->dataFactory->createLuminousCalibrate("HLuminousCalibrate");
        auto luminouss = d->dataFactory->createLuminousCalibrateCollection("HLuminousCalibrateCollection");
        luminousItem1->setData("[项类型]", "[光通量]");
        luminousItem2->setData("[项类型]", "[光强度]");
        luminous->insert("[光通量]", luminousItem1);
        luminous->insert("[光强度]", luminousItem2);
        luminous->setTotalGears(5);
        luminouss->insert("模块1", luminous);

        auto chromatisms = d->dataFactory->createChromatismCollection("HChromatismCollection");
        chromatisms->dataStream()->readFile(":/dat/Chromatism.hcc");

        d->configManage->setContain(IConfigManage::ContainSpec
                                    | IConfigManage::ContainElec
                                    | IConfigManage::ContainLuminous
                                    | IConfigManage::ContainChromatism
                                    | IConfigManage::ContainGrade
                                    | IConfigManage::ContainLocation
                                    | IConfigManage::ContainAdjust
                                    | IConfigManage::ContainQuality);
        d->configManage->setSpecCalibrateCollection(specs);
        d->configManage->setElecCalibrateCollection(elecs);
        d->configManage->setLuminousCalibrateCollection(luminouss);
        d->configManage->setChromatismCollection(chromatisms);
        d->configManage->setGradeCollection(d->dataFactory->createGradeCollection("HGradeCollection"));
        d->configManage->setAdjustCollection(d->dataFactory->createAdjustCollection("HAdjustCollection"));
        d->configManage->setLocationCollection(d->dataFactory->createLocationCollection("LocationCollection"));
        d->configManage->addQualityCollection("Spec", d->dataFactory->createQualityCollection("HQualityCollection"));
    }
    HAppContext::setContextPointer("IConfigManage", d->configManage);
}

void HBuilder7000::buildTestData()
{
    Q_D(HBuilder7000);
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

void HBuilder7000::buildTemplate()
{
    Q_D(HBuilder7000);
    auto textExport = d->dataFactory->createTextExport("HTextExport");
    auto specTextTemplate = d->guiFactory->createTextExportTemplate("HSpecTextExportTemplate");
    HAppContext::setContextPointer("ITextExport", textExport);
    HAppContext::setContextPointer("ISpecTextExportTemplate", specTextTemplate);
}

void HBuilder7000::buildDevice()
{
    Q_D(HBuilder7000);
#ifdef SIMULATE // 模拟设备
    auto device1 = d->communicateFactory->createDevice("HSpecSimulateDevice");
    auto device2 = d->communicateFactory->createDevice("HSimulateDevice");
    auto device3 = d->communicateFactory->createDevice("HSimulateDevice");
    auto convert1 = d->communicateFactory->createUCharConvert("HLittleUCharConvert");
    auto convert2 = d->communicateFactory->createUCharConvert("HLittleUCharConvert");
    auto convert3 = d->communicateFactory->createUCharConvert("HLittleUCharConvert");
    auto protocol1 = d->communicateFactory->createProtocol("HProtocol");
    auto protocol2 = d->communicateFactory->createProtocol("HProtocol");
    auto protocol3 = d->communicateFactory->createProtocol("HProtocol");
    protocol1->setConvert(convert1);
    protocol1->setDevice(device1);
    protocol2->setConvert(convert2);
    protocol2->setDevice(device2);
    protocol3->setConvert(convert3);
    protocol3->setDevice(device3);
#else
    auto protocol1 = d->communicateFactory->createProtocol(deployItem("CcdProtocol"));
    auto protocol2 = d->communicateFactory->createProtocol("HSl1000Protocol");
    auto protocol3 = new HKeyenceProtocol();
#endif
    auto protocols = d->communicateFactory->createProtocolCollection("HProtocolCollection");
    protocols->insert("Spec", protocol1);
    protocols->insert("Else", protocol2);
    protocols->insert("Keyence", protocol3);
    HAppContext::setContextPointer("IProtocolCollection", protocols);
}

void HBuilder7000::buildThread()
{
    Q_D(HBuilder7000);
    auto thread = new HThread7000(this);
    auto threads = d->controllerFactory->createThreadCollection("HThreadCollection");
    threads->insert("1", thread);
    HAppContext::setContextPointer("IThreadCollection", threads);
}

void HBuilder7000::buildModel()
{
    auto model = new HModel7000(this);
    HAppContext::setContextPointer("IModel", model);
}

void HBuilder7000::buildMemento()
{
    Q_D(HBuilder7000);
    auto mementos = d->controllerFactory->createMementoCollection("HMementoCollection");
    if (!mementos->readFile(QString("%1.tmp").arg(QApplication::applicationName())) || !mementos->contains("Spec"))
    {
        auto memento = d->controllerFactory->createMemento("HMemento");
        memento->setDataType(QStringList() << "[积分时间]" << "[输出电流_档位]" << "[实测电流_档位]" << "[输出电压]" << "[输出电流]" << "[反向电压]" << "[光测试类型]" << "[光档位]");
        mementos->insert("Spec", memento);
    }
    HAppContext::setContextPointer("IMementoCollection", mementos);
}

void HBuilder7000::buildDatabase()
{

}

void HBuilder7000::buildMenu()
{
    Q_D(HBuilder7000);
    QVariantMap param[2];
    param[0].insert("authority", 1);
    param[1].insert("property", param[0]);
    auto calibrate = new QMenu(tr("定标(&C)"));
    auto location = new QMenu(tr("定位配置(&T)"));
    auto grade = new QMenu(tr("分级(&G)"));
    auto adjust = new QMenu(tr("调整(&A)"));
    auto quality = new QMenu(tr("品质(&Q)"));
    auto device = new QMenu(tr("设备配置(&T)"));
    auto account = new QMenu(tr("账号管理(&M)"));
    calibrate->menuAction()->setProperty("authority", 1);
    location->menuAction()->setProperty("authority", 1);
    grade->menuAction()->setProperty("authority", 1);
    quality->menuAction()->setProperty("authority", 1);
    device->menuAction()->setProperty("authority", 1);
    calibrate->addAction(d->guiFactory->createAction(tr("光谱定标(&S)..."), "HSpecCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("电定标(&E)..."), "HElecCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("光定标(&E)..."), "HLuminousCalibrateHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("光通量自吸收配置(&L)..."), "HSpecLuminousHandler"));
    calibrate->addAction(d->guiFactory->createAction(tr("色温配置(&T)..."), "HSpecTcHandler"));
    location->addAction(d->guiFactory->createAction(tr("定位数据配置(&E)..."), "HLocationEditHandler"));
    location->addAction(d->guiFactory->createAction(tr("定位数据选择(&S)..."), "HLocationSelectHandler"));
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
    account->addAction(d->guiFactory->createAction(tr("管理员登入(&I)..."), "HLoginInHandler"));
    account->addAction(d->guiFactory->createAction(tr("注销(&O)..."), "HLoginOutHandler"));
    d->mainWindow->insertMenu(calibrate);
    d->mainWindow->insertMenu(location);
    d->mainWindow->insertMenu(grade);
    d->mainWindow->insertMenu(adjust);
    d->mainWindow->insertMenu(quality);
    d->mainWindow->insertMenu(device);
    d->mainWindow->insertMenu(account);
#ifndef QT_DEBUG
    d->mainWindow->setAuthority(0);
#endif
}

void HBuilder7000::buildTestWidget()
{
    ITestWidget *widget = new HTestWidget7000;
    HAppContext::setContextPointer("ITestWidget", widget);
}
