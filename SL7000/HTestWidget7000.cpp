#include "HTestWidget7000_p.h"
#include "HeCore/HCore.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include "HeController/IMementoCollection.h"
#include <QtCore/QSettings>
#include <QtGui/QCloseEvent>

HTestWidget7000Private::HTestWidget7000Private()
{
    auto group = QStringList() << "|时间信息2|" << "|产品信息3|" << "|环境信息|"  << "|直流电信息|" << "|光度信息|" << "|光谱信息5|" << "|色容差信息2|" << "|光合信息|" << "|TM30信息2|";
    auto mementoCollection = HAppContext::getContextPointer<IMementoCollection>("IMementoCollection");
    memento = mementoCollection->value("Spec");
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
    displays = QStringList() << "[调整组]" << "[分级]" << HCore::membership(group);
}

HTestWidget7000::HTestWidget7000(QWidget *parent) :
    HTestWidget(*new HTestWidget7000Private, parent)
{
    init();
}

HTestWidget7000::~HTestWidget7000() = default;

QString HTestWidget7000::typeName()
{
    return "HTestWidget7000";
}

void HTestWidget7000::init()
{
    Q_D(HTestWidget7000);
    readSettings();
//    d->testResult = new HTestResult(this);
//    d->testResult->setSyncType(d->displays);
//    d->testResult->setSyncFile(d->syncFile);
//    d->textExport->setExportPath(d->exportPath);
//    d->timer = new QTimer(this);
//    d->timer->setInterval(d->syncInterval * 1000);
//    connect(d->timer, &QTimer::timeout, this, [=] { d->testResult->syncFile(); });
    HTestWidget::init();
    resetGrade();
    resetLocation();
}

void HTestWidget7000::closeEvent(QCloseEvent *event)
{
    stop();
    clearResult();
    writeSettings();
    event->accept();
}

void HTestWidget7000::handleAction(HActionType action)
{

}

void HTestWidget7000::readSettings()
{
}

void HTestWidget7000::writeSettings()
{
}
