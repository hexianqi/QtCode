#include "HTestWidget2000DC_p.h"
#include "HTestSetWidget2000DC.h"
#include "HDetailWidget2000DC.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeData/ITestData.h"
#include "HeGui/HSpecEnergyWidget.h"
#include <QtCore/QSettings>
#include <QtWidgets/QMenu>

HTestWidget2000DCPrivate::HTestWidget2000DCPrivate()
{
    auto list = QStringList() << "|时间信息2|" << "|产品信息3|" << "|环境信息|"  << "|直流电信息|" << "|光度信息2|" << "|光谱信息5|" << "|色容差信息2|" << "|光合信息|" << "|TM30信息2|";
    displays = QStringList() << "[调整组]" << "[分级]" << HCore::membership(list);
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
    d->energyWidget->addProgressBar("[光采样比率]");
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
    HSpecTestWidget::createWidget();
    d->testSetWidget = new HTestSetWidget2000DC;
    d->detailWidget = new HDetailWidget2000DC;
}

void HTestWidget2000DC::createMenu()
{
    Q_D(HTestWidget2000DC);
    HSpecTestWidget::createMenu();
    d->menus.at(0)->addAction(d->actionProbe);
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
