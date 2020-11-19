#include "HTestWidget2000DC_p.h"
#include "HTestSetWidget2000DC.h"
#include "HDetailWidget2000DC.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include "HeGui/HSpecEnergyWidget.h"
#include "HeGui/HResultTableWidget.h"
#include "HeGui/HTestDataEditDialog.h"
#include <QtWidgets/QMenu>
#include <QtCore/QSettings>
#include <QtCore/QDebug>

HTestWidget2000DCPrivate::HTestWidget2000DCPrivate()
{
    displays = QStringList() << "[测量日期]" << "[测量时间]" << "[制造厂商]" << "[产品型号]" << "[测试员]" << "[样品编号]" << "[备注]" << "[环境温度]" << "[环境湿度]"
                             << "[分级]"
                             << "[输出电压]" << "[实测电压]" << "[输出电流]" << "[实测电流]" << "[反向电压]" << "[反向漏流]" << "[电功率]"
                             << "[色容差]"
                             << "[光通量]" << "[光功率]" << "[光效率]"
                             << "[主波长]" << "[峰值波长]" << "[峰值带宽]"
                             << "[色温]" << "[色纯度]"
                             << "[色坐标x]" << "[色坐标y]" << "[色坐标up]" << "[色坐标vp]" << "[Duv]"
                             << "[红色比]" << "[绿色比]" << "[蓝色比]"
                             << "[显色指数Ra]" << "[显色指数R9]" <<"[显色指数Rx]";
    testSetWidget = new HTestSetWidget2000DC;
    detailWidget = new HDetailWidget2000DC;
    energyWidget->addProgressBar("[光采样比率]");
}

HTestWidget2000DC::HTestWidget2000DC(QWidget *parent) :
    HTestWidget2000(*new HTestWidget2000DCPrivate, parent)
{
    init();
}

HTestWidget2000DC::HTestWidget2000DC(HTestWidget2000DCPrivate &p, QWidget *parent) :
    HTestWidget2000(p, parent)
{
}

HTestWidget2000DC::~HTestWidget2000DC()
{
    qDebug() << __func__;
}

QString HTestWidget2000DC::typeName()
{
    return "HTestWidget2000DC";
}

void HTestWidget2000DC::init()
{
    Q_D(HTestWidget2000DC);
    HTestWidget2000::init();
    connect(d->resultWidget, &HResultTableWidget::itemDoubleClicked, this, &HTestWidget2000DC::editProductInfo);
    setProbe(d->testData->data("[使用光探头]").toBool());
}

void HTestWidget2000DC::createAction()
{
    Q_D(HTestWidget2000DC);
    HTestWidget2000::createAction();
    d->actionProbe = new QAction(tr("使用光探头(&P)"), this);
    d->actionProbe->setCheckable(true);
    d->actionProbe->setChecked(d->testData->data("[使用光探头]").toBool());
    d->actionProductInfo = new QAction(tr("产品信息修改(&P)"), this);
    d->resultWidget->addAction(d->actionProductInfo);
    connect(d->actionProbe, &QAction::triggered, this, &HTestWidget2000DC::setProbe);
    connect(d->actionProductInfo, &QAction::triggered, this, &HTestWidget2000DC::editProductInfo);
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
    settings->beginGroup("ProductInfo");
    d->testData->setData("[制造厂商]", settings->value("Manufacturer", "Manufacturer"));
    d->testData->setData("[产品名称]", settings->value("ProductName", "Name"));
    d->testData->setData("[产品型号]", settings->value("ProductModel", "Model"));
    d->testData->setData("[测试员]", settings->value("Tester", ""));
    d->testData->setData("[备注]", settings->value("Note", ""));
    d->testData->setData("[样品编号]", settings->value("SampleNumber", 1));
    d->testData->setData("[环境温度]", settings->value("Temperature", 25.0));
    d->testData->setData("[环境湿度]", settings->value("Humidity", 60.0));
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
    settings->beginGroup("ProductInfo");
    settings->setValue("Manufacturer", d->testData->data("[制造厂商]"));
    settings->setValue("ProductName", d->testData->data("[产品名称]"));
    settings->setValue("ProductModel", d->testData->data("[产品型号]"));
    settings->setValue("Tester", d->testData->data("[测试员]"));
    settings->setValue("Note", d->testData->data("[备注]"));
    settings->setValue("SampleNumber", d->testData->data("[样品编号]"));
    settings->setValue("Temperature", d->testData->data("[环境温度]"));
    settings->setValue("Humidity", d->testData->data("[环境湿度]"));
    settings->endGroup();
}

void HTestWidget2000DC::setProbe(bool b)
{
    Q_D(HTestWidget2000DC);
    d->testData->setData("[使用光探头]", b);
    d->energyWidget->setProgressBarVisible("[光采样比率]", b);
    d->testSetWidget->handleOperation("<启用光挡位>", b);
}

void HTestWidget2000DC::editProductInfo()
{
    Q_D(HTestWidget2000DC);
    auto row = d->resultWidget->currentRow();
    auto data = d->results.at(row);
    HTestDataEditDialog dlg(this);
    dlg.setData(data);
    if (dlg.exec() != QDialog::Accepted)
        return;
    d->resultWidget->setRow(row, data->toString(d->displays));
}
