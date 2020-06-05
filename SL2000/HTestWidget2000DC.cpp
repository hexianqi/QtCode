#include "HTestWidget2000DC_p.h"
#include "HTestSetWidget2000DC.h"
#include "HDetailWidget2000DC.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include "HeGui/HSpecEnergyWidget.h"
#include <QtWidgets/QMenu>
#include <QtCore/QSettings>
#include <QtCore/QDebug>

HTestWidget2000DCPrivate::HTestWidget2000DCPrivate()
{
    displays = QStringList() << "[测量日期]" << "[测量时间]"
                             << "[分级]"
                             << "[输出电压]" << "[实测电压]" << "[输出电流]" << "[实测电流]" << "[反向电压]" << "[反向漏流]" << "[电功率]"
                             << "[色容差]"
                             << "[光通量]" << "[光功率]" << "[光效率]"
                             << "[主波长]" << "[峰值波长]" << "[峰值带宽]"
                             << "[色温]" << "[色纯度]"
                             << "[色坐标]" << ("[色坐标uvp]") << "[Duv]"
                             << "[红色比]" << "[绿色比]" << "[蓝色比]"
                             << "[显色指数]" <<"[显色指数Rx]";
    testSetWidget = new HTestSetWidget2000DC;
    detailWidget = new HDetailWidget2000DC;
    energyWidget->addProgressBar("[光采样比率]");
}

HTestWidget2000DC::HTestWidget2000DC(QWidget *parent) :
    HTestWidget2000(*new HTestWidget2000DCPrivate, parent)
{
    readSettings();
    init();
}

HTestWidget2000DC::HTestWidget2000DC(HTestWidget2000DCPrivate &p, QWidget *parent) :
    HTestWidget2000(p, parent)
{
}

HTestWidget2000DC::~HTestWidget2000DC()
{
    qDebug() << __func__;
    writeSettings();
}

QString HTestWidget2000DC::typeName()
{
    return "HTestWidget2000DC";
}

void HTestWidget2000DC::handleAction(HActionType action)
{
    if (action == ACT_SINGLE_TEST || action == ACT_GET_SPECTRUM_ELEC)
    {
        postProcess();
        refreshWidget();
    }
    HTestWidget2000::handleAction(action);
}

void HTestWidget2000DC::createAction()
{
    Q_D(HTestWidget2000DC);
    HTestWidget2000::createAction();
    d->actionProbe = new QAction(tr("使用光探头(&P)"), this);
    d->actionProbe->setCheckable(true);
    d->actionProbe->setChecked(d->testData->data("[使用光探头]").toBool());
    connect(d->actionProbe, &QAction::triggered, this, [=](bool b){ d->testData->setData("[使用光探头]", b); });
}

void HTestWidget2000DC::createMenu()
{
    Q_D(HTestWidget2000DC);
    HTestWidget2000::createMenu();
    d->menus.at(0)->insertAction(d->actionAdjust, d->actionProbe);
}

void HTestWidget2000DC::readSettings()
{
    Q_D(HTestWidget2000DC);
    HTestWidget2000::readSettings();
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup("TestWidget");
    d->testData->setData("[使用光探头]", settings->value("Probe", false));
    settings->endGroup();
}

void HTestWidget2000DC::writeSettings()
{
    Q_D(HTestWidget2000DC);
    HTestWidget2000::writeSettings();
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup("TestWidget");
    settings->setValue("Probe", d->testData->data("[使用光探头]"));
    settings->endGroup();
}
