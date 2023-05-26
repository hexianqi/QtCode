#include "HTestWidget1000I_p.h"
#include "HTestSetWidget1000I.h"
#include "HDetailWidget1000I.h"
#include "HeCore/HCore.h"
#include "HeCore/HAppContext.h"
#include "HeController/IMementoCollection.h"
#include "HeData/ITestData.h"
#include "HeData/ITextExport.h"
#include "HeData/ITextExportTemplate.h"
#include "HeGui/HSyncTestResult.h"
#include "HeGui/HSpecEnergyWidget.h"
#include "HeGui/HResultTableWidget.h"
#include "HeSql/ISqlHandle.h"
#include "HeSql/HSql.h"
#include <QtCore/QSettings>
#include <QtCore/QTimer>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolBar>

HTestWidget1000IPrivate::HTestWidget1000IPrivate()
{
    auto list = QStringList() << "|时间信息2|" << "|产品信息3|" << "|环境信息|"  << "|直流电信息|";
    displays = QStringList() << "[调整组]" << "[分级]" << HCore::membership(list) << "[辐射强度]" << "[辐射通量]"  << "[峰值波长]";
    auto mementoCollection = HAppContext::getContextPointer<IMementoCollection>("IMementoCollection");
    memento = mementoCollection->value("SpecI");
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
    sqlHandle = HAppContext::getContextPointer<ISqlHandle>("ISpecISqlHandle");
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

void HTestWidget1000I::handleAction(HActionType action)
{
    Q_D(HTestWidget1000I);
    if (action >= 0xF0000000)
    {
        setTest(false);
        clearResult();
        if (action == ACT_RESET_SPECTRUM)
            d->energyWidget->initCoordinate();
        return;
    }
    HTestWidget::handleAction(action);
}

void HTestWidget1000I::createAction()
{
    Q_D(HTestWidget1000I);
    HTestWidget::createAction();
    d->actionPrintPreview = new QAction(tr("打印预览(&V)"), this);
    d->actionPrintPreview->setIcon(QIcon(":/image/PrintPreview.png"));
    d->actionPrintPreview->setIconText(tr("打印预览"));
    d->actionPrintPreview->setEnabled(false);
    d->actionExportDatabaseLast = new QAction(tr("保存数据库(&D)"), this);
    d->actionExportDatabaseLast->setIcon(QIcon(":/image/DbComit.png"));
    d->actionExportDatabaseLast->setIconText(tr("保存数据库"));
    d->actionExportDatabaseLast->setEnabled(false);
    d->actionExportDatabase = new QAction(tr("保存数据库(&D)"), this);
    d->actionExportDatabase->setIcon(QIcon(":/image/DbComit.png"));
    d->actionExportDatabase->setIconText(tr("保存数据库"));
    d->actionRemove = new QAction(tr("删除记录(&R)"), this);
    d->actionRemove->setIcon(QIcon(":/image/Remove.png"));
    d->actionRemove->setIconText(tr("删除记录"));
    d->actionAdjust = new QAction(tr("使用调整(&A)"), this);
    d->actionAdjust->setCheckable(true);
    d->actionAdjust->setChecked(d->testData->data("[使用调整]").toBool());
    d->actionExportPath = new QAction(tr("配置导出目录(&D)"), this);
    d->actionSyncFile = new QAction(tr("配置同步文件(&F)"), this);
    connect(d->actionPrintPreview, &QAction::triggered, this, &HTestWidget1000I::printPreview);
    connect(d->actionExportDatabaseLast, &QAction::triggered, this, &HTestWidget1000I::exportDatabaseLast);
    connect(d->actionExportDatabase, &QAction::triggered, this, &HTestWidget1000I::exportDatabase);
    connect(d->actionRemove, &QAction::triggered, this, &HTestWidget1000I::removeResult);
    connect(d->actionAdjust, &QAction::triggered, this, [=](bool b){ d->testData->setData("[使用调整]", b); });
    connect(d->actionExportPath, &QAction::triggered, this, &HTestWidget1000I::setExportPath);
    connect(d->actionSyncFile, &QAction::triggered, this, &HTestWidget1000I::setSyncFile);
}

void HTestWidget1000I::createWidget()
{
    Q_D(HTestWidget1000I);
    d->energyWidget = new HSpecEnergyWidget;
    d->tableWidget = new HResultTableWidget;
    d->testSetWidget = new HTestSetWidget1000I;
    d->detailWidget = new HDetailWidget1000I;
    d->energyWidget->addProgressBar("[光采样比率]");
    d->energyWidget->setToolTipTypes();
}

void HTestWidget1000I::createMenu()
{
    Q_D(HTestWidget1000I);
    auto menu = new QMenu(tr("测试配置(&T)"));
    menu->addAction(d->actionAdjust);
    menu->addAction(d->actionExportPath);
    menu->addAction(d->actionSyncFile);
    d->menus << menu;
}

void HTestWidget1000I::createToolBar()
{
    Q_D(HTestWidget1000I);
    auto toolBar1 = new QToolBar(tr("设置(&S)"));
    auto toolBar2 = new QToolBar(tr("操作(&O)"));
    toolBar1->addWidget(d->testSetWidget);
    toolBar2->addAction(d->actionStart);
    toolBar2->addAction(d->actionStop);
    toolBar2->addAction(d->actionClear);
    toolBar2->addAction(d->actionExportExcel);
    toolBar2->addAction(d->actionExportDatabaseLast);
    toolBar2->addAction(d->actionPrintPreview);
    d->toolBars << toolBar1 << toolBar2;
}

void HTestWidget1000I::initWidget()
{
    Q_D(HTestWidget1000I);
    auto layout = new QGridLayout(this);
    auto tabWidget1 = new QTabWidget;
    auto tabWidget2 = new QTabWidget;
    auto splitter = new QSplitter(Qt::Vertical);
    d->tableWidget->setDisplay(d->displays);
    d->tableWidget->setSelected(d->tableSelecteds);
    d->tableWidget->addAction(d->actionClear);
    d->tableWidget->addAction(d->actionRemove);
    d->tableWidget->addAction(d->actionExportDatabase);
    tabWidget1->addTab(d->energyWidget, d->energyWidget->windowTitle());
    tabWidget2->addTab(d->detailWidget, tr("当次结果"));
    tabWidget2->addTab(d->tableWidget, tr("结果列表"));
    splitter->addWidget(tabWidget1);
    splitter->addWidget(tabWidget2);
    splitter->setHandleWidth(15);
    splitter->setStretchFactor(1, 1);
    layout->addWidget(splitter);
    connect(d->testSetWidget, &ITestSetWidget::testStateChanged, this, &HTestWidget1000I::handleStateChanged);
    connect(d->testSetWidget, &ITestSetWidget::saveModeChanged, this, &HTestWidget1000I::handleSaveModeChanged);
    connect(d->testSetWidget, &ITestSetWidget::resultChanged, this, &HTestWidget1000I::handleResultChanged);
//    connect(d->testSetWidget, SIGNAL(testStateChanged(bool)), this, SLOT(handleStateChanged(bool)));
//    connect(d->testSetWidget, SIGNAL(saveModeChanged(int)), this, SLOT(handleSaveModeChanged(int)));
    //    connect(d->testSetWidget, SIGNAL(resultChanged(HActionType, bool)), this, SLOT(handleResultChanged(HActionType, bool)));
}

void HTestWidget1000I::clearResult()
{
    Q_D(HTestWidget1000I);
    d->testResult->clear();
    d->textExport->clear();
    d->tableWidget->clearResult();
}

void HTestWidget1000I::saveResult()
{
    Q_D(HTestWidget1000I);
    if (d->testResult->isEmpty())
        return;
    if (QMessageBox::question(this, tr("保存数据"), tr("是否保存到数据库？")) == QMessageBox::Yes)
        exportDatabaseRange(0, d->testResult->size());
}

void HTestWidget1000I::exportExcel()
{
    Q_D(HTestWidget1000I);
    auto data = d->testResult->last();
    if (data == nullptr)
        return;

    auto type = QStringList() << d->displays << "[光谱能量曲线]";
    d->textExportTemplate->setDataType(type);
    d->textExportTemplate->setData(data->select(type));
    d->textExport->setTextTemplate(d->textExportTemplate);
    d->textExport->saveAs();
}

void HTestWidget1000I::readSettings()
{
    Q_D(HTestWidget1000I);
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("SpecTestWidget");
    d->tableSelecteds = settings->value("TableSelected", d->displays).toStringList();
    d->exportPath = settings->value("ExportPath", ".").toString();
    d->syncFile = settings->value("SyncFile", "temp.xlsx").toString();
    d->syncInterval = settings->value("SyncInterval", 20).toInt();
    d->testData->setData("[使用调整]", settings->value("Adjust", false));
    d->testData->setData("[CCD偏差]", settings->value("Offset", 55.0));
    settings->endGroup();
    d->testData->handleOperation("<读取配置>", fileName);
}

void HTestWidget1000I::writeSettings()
{
    Q_D(HTestWidget1000I);
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("SpecTestWidget");
    settings->setValue("TableSelected", d->tableWidget->selected());
    settings->setValue("ExportPath", d->exportPath);
    settings->setValue("SyncFile", d->syncFile);
    settings->setValue("SyncInterval", d->syncInterval);
    settings->setValue("Adjust", d->testData->data("[使用调整]"));
    settings->setValue("Offset", d->testData->data("[CCD偏差]"));
    settings->endGroup();
    d->testData->handleOperation("<写入配置>", fileName);
}

void HTestWidget1000I::handleStateChanged(bool b)
{
    Q_D(HTestWidget1000I);
    d->actionStart->setEnabled(!b);
    d->actionStop->setEnabled(b);
    d->actionClear->setEnabled(!b);
    d->actionPrintPreview->setEnabled(!b);
    d->actionExportExcel->setEnabled(!b);
    d->actionExportDatabase->setEnabled(!b);
    d->actionExportDatabaseLast->setEnabled(!b);
}

void HTestWidget1000I::handleSaveModeChanged(int value)
{
    Q_D(HTestWidget1000I);
    if (value == 2)
        d->timer->start();
    else
        d->timer->stop();
}

void HTestWidget1000I::handleResultChanged(HActionType, bool append)
{
    Q_D(HTestWidget1000I);
    postProcess(append);
    refreshWidget(append);
    d->testResult->update(append);
    if (d->testSetWidget->saveMode() == 1 && append)
        exportExcelAppend();
}

void HTestWidget1000I::exportExcelAppend()
{
    Q_D(HTestWidget1000I);
    auto data = d->testResult->last();
    if (data == nullptr)
        return;

    d->textExportTemplate->setDataType(d->displays);
    d->textExportTemplate->setData(data->select(d->displays));
    d->textExport->setTextTemplate(d->textExportTemplate);
    d->textExport->append();
}

void HTestWidget1000I::exportDatabase()
{
    Q_D(HTestWidget1000I);
    for (const auto &range : d->tableWidget->selectedRanges())
        exportDatabaseRange(range.topRow(), range.rowCount());
}

void HTestWidget1000I::exportDatabaseLast()
{
    Q_D(HTestWidget1000I);
    auto data = d->testResult->last();
    if (data == nullptr)
        return;
    auto record = HSql::toRecord(d->sqlHandle->field(), data);
    d->sqlHandle->addRecord(record);
}
