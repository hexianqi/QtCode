#include "HBuilder2000F_p.h"
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
#include "HeGui/IGuiFactory.h"
#include "HeGui/IMainWindow.h"
#include "HeGui/HAction.h"
#include <QtWidgets/QMenu>

HBuilder2000F::HBuilder2000F(QObject *parent) :
    HBuilder2000DC(*new HBuilder2000FPrivate, parent)
{
}

HBuilder2000F::~HBuilder2000F() = default;

QString HBuilder2000F::typeName()
{
    return "HBuilder2000F";
}

void HBuilder2000F::buildConfigManage()
{
    Q_D(HBuilder2000F);
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
        luminousItem->setData("[项类型]", "[光通量]");
        luminousItem->setTotalGears(5);
        luminous->insert("[光通量]", luminousItem);
        luminouss->insert("模块1", luminous);

        auto chromatisms = d->dataFactory->createChromatismCollection("HChromatismCollection");
        chromatisms->dataStream()->readFile(":/dat/Chromatism.hcc");

        d->configManage->setContain(IConfigManage::ContainSpec
                                    | IConfigManage::ContainElec
                                    | IConfigManage::ContainLuminous
                                    | IConfigManage::ContainChromatism
                                    | IConfigManage::ContainGrade
                                    | IConfigManage::ContainAdjust2
                                    | IConfigManage::ContainQuality);
        d->configManage->setSpecCalibrateCollection(specs);
        d->configManage->setElecCalibrateCollection(elecs);
        d->configManage->setLuminousCalibrateCollection(luminouss);
        d->configManage->setChromatismCollection(chromatisms);
        d->configManage->setGradeCollection(d->dataFactory->createGradeCollection("HGradeCollection"));
        d->configManage->setAdjust2Collection(d->dataFactory->createAdjust2Collection("HAdjust2Collection"));
        d->configManage->setQualityCollection(d->dataFactory->createQualityCollection("HQualityCollection"));
    }
    HAppContext::setContextPointer("IConfigManage", d->configManage);
}

void HBuilder2000F::buildMenu()
{
    Q_D(HBuilder2000F);
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
    adjust->addAction(d->guiFactory->createAction(tr("调整数据配置(&E)..."), "HAdjust2EditHandler", param[0]));
    adjust->addAction(d->guiFactory->createAction(tr("调整数据选择(&S)..."), "HAdjust2SelectHandler"));
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
