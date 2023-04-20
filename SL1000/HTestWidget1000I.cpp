#include "HTestWidget1000I_p.h"
#include "HeCore/HCore.h"
#include "HeCore/HAppContext.h"
#include "HeController/IMementoCollection.h"
#include "HeGui/HSyncTestResult.h"

HTestWidget1000IPrivate::HTestWidget1000IPrivate()
{
    auto list = QStringList() << "|时间信息2|" << "|产品信息3|" << "|环境信息|"  << "|直流电信息|";
    displays = QStringList() << "[调整组]" << "[分级]" << HCore::membership(list) << "[辐射强度]" << "[辐射通量]"  << "[峰值波长]";
    auto mementoCollection = HAppContext::getContextPointer<IMementoCollection>("IMementoCollection");
    memento = mementoCollection->value("Spec");
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
    sqlHandle = HAppContext::getContextPointer<ISqlHandle>("ISpecSqlHandle");
    print = HAppContext::getContextPointer<IPrint>("IPrint");
    printTemplate = HAppContext::getContextPointer<IPrintTemplate>("ISpecPrintTemplate");
    textExport = HAppContext::getContextPointer<ITextExport>("ITextExport");
    textExportTemplate = HAppContext::getContextPointer<ITextExportTemplate>("ISpecTextExportTemplate");
}

HTestWidget1000I::HTestWidget1000I(QWidget *parent) :
    HTestWidget(*new HTestWidget1000IPrivate, parent)
{
    init();
}

HTestWidget1000I::~HTestWidget1000I() = default;

QString HTestWidget1000I::typeName()
{
    return "HTestWidget1000I";
}

void HTestWidget1000I::init()
{
    Q_D(HTestWidget1000I);
    HTestWidget::init();
    d->testResult = new HSyncTestResult(this);
    d->testResult->setSyncType(d->displays);
    d->testResult->setSyncFile(d->syncFile);
    d->textExport->setExportPath(d->exportPath);
    d->timer = new QTimer(this);
    d->timer->setInterval(d->syncInterval * 1000);
    connect(d->timer, &QTimer::timeout, this, [=] { d->testResult->syncFile(); });
}

void HTestWidget1000I::createWidget()
{
    Q_D(HTestWidget1000I);
    HSpecTestWidget::createWidget();
    d->testSetWidget = new HTestSetWidget1000A;
    d->detailWidget = new HDetailWidget1000A;
    d->energyWidget->addProgressBar("[光采样比率]");
}



