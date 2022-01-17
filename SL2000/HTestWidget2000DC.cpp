#include "HTestWidget2000DC_p.h"
#include "HTestSetWidget2000DC.h"
#include "HDetailWidget2000DC.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include "HeGui/HSpecEnergyWidget.h"
#include <QtCore/QSettings>
#include <QtWidgets/QMenu>

HTestWidget2000DCPrivate::HTestWidget2000DCPrivate()
{
    displays = QStringList() << "[调整组]"
                             << "[测量日期]" << "[测量时间]" << "[制造厂商]" << "[产品型号]" << "[测试员]" << "[样品编号]" << "[备注]" << "[环境温度]" << "[环境湿度]"
                             << "[分级]"
                             << "[输出电压]" << "[实测电压]" << "[输出电流]" << "[实测电流]" << "[反向电压]" << "[反向漏流]" << "[电功率]"
                             << "[色容差]"
                             << "[光通量]" << "[光功率]" << "[光效率]"
                             << "[主波长]" << "[峰值波长]" << "[峰值带宽]"
                             << "[色温]" << "[色纯度]"
                             << "[色坐标x]" << "[色坐标y]" << "[色坐标up]" << "[色坐标vp]" << "[Duv]"
                             << "[红色比]" << "[绿色比]" << "[蓝色比]"
                             << "[显色指数Ra]" << "[显色指数R9]" <<"[显色指数Rx]"
                             << "[光量子(380-780)]" << "[光量子(400-700)]" << "[光量子(700-800)]"
                             << "[光合光量子通量]" << "[光合有效辐射通量]" << "[光合光子通量效率]"
                             << "[荧光效能]" << "[荧光蓝光比]"
                             << "[TM30_Rf]" << "[TM30_Rg]";
}

HTestWidget2000DC::HTestWidget2000DC(QWidget *parent) :
    HSpecTestWidget(*new HTestWidget2000DCPrivate, parent)
{
    init();
}

HTestWidget2000DC::~HTestWidget2000DC() = default;

QString HTestWidget2000DC::typeName()
{
    return "HTestWidget2000DC";
}

void HTestWidget2000DC::init()
{
    Q_D(HTestWidget2000DC);
    HSpecTestWidget::init();
    setProbe(d->testData->data("[使用光探头]").toBool());
}

void HTestWidget2000DC::createAction()
{
    Q_D(HTestWidget2000DC);
    HSpecTestWidget::createAction();
    d->actionProbe = new QAction(tr("使用光探头(&P)"), this);
    d->actionProbe->setCheckable(true);
    d->actionProbe->setChecked(d->testData->data("[使用光探头]").toBool());
    connect(d->actionProbe, &QAction::triggered, this, &HTestWidget2000DC::setProbe);
}

void HTestWidget2000DC::createWidget()
{
    Q_D(HTestWidget2000DC);
    d->testSetWidget = new HTestSetWidget2000DC;
    d->detailWidget = new HDetailWidget2000DC;
    HSpecTestWidget::createWidget();
}

void HTestWidget2000DC::createMenu()
{
    Q_D(HTestWidget2000DC);
    HSpecTestWidget::createMenu();
    d->menus.at(0)->addAction(d->actionProbe);
}

void HTestWidget2000DC::initWidget()
{
    Q_D(HTestWidget2000DC);
    HSpecTestWidget::initWidget();
    d->energyWidget->addProgressBar("[光采样比率]");
}

void HTestWidget2000DC::readSettings()
{
    Q_D(HTestWidget2000DC);
    HSpecTestWidget::readSettings();
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("TestWidget");
    d->testData->setData("[使用光探头]", settings->value("Probe", false));
    settings->endGroup();
}

void HTestWidget2000DC::writeSettings()
{
    Q_D(HTestWidget2000DC);
    HSpecTestWidget::writeSettings();
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("TestWidget");
    settings->setValue("Probe", d->testData->data("[使用光探头]"));
    settings->endGroup();
}

void HTestWidget2000DC::setProbe(bool b)
{
    Q_D(HTestWidget2000DC);
    d->testData->setData("[使用光探头]", b);
    d->energyWidget->setProgressBarVisible("[光采样比率]", b);
    d->testSetWidget->handleOperation("<启用光挡位>", b);
}
