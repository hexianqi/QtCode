#include "HSpecTestWidget_p.h"
#include "HGuiHelper.h"
#include "ITestDetailWidget.h"
#include "ITestSetWidget.h"
#include "HTestResult.h"
#include "HSpecEnergyWidget.h"
#include "HSpecChromatismChartView.h"
#include "HResultTableWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IGradeCollection.h"
#include "HeData/ITestData.h"
#include "HeController/IMemento.h"
#include "HePlugin/HCie1931Widget.h"
#include <QtCore/QDateTime>
#include <QtCore/QSettings>
#include <QtCore/QTimer>
#include <QtGui/QCloseEvent>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMenu>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolBar>

HE_GUI_BEGIN_NAMESPACE

HSpecTestWidgetPrivate::HSpecTestWidgetPrivate()
{
    testData->setData("[使用调整]", false);
    memento = HAppContext::getContextPointer<IMemento>("IMementoTest");
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
}

HSpecTestWidget::HSpecTestWidget(QWidget *parent) :
    HTestWidget(*new HSpecTestWidgetPrivate, parent)
{
}

HSpecTestWidget::HSpecTestWidget(HSpecTestWidgetPrivate &p, QWidget *parent) :
    HTestWidget(p, parent)
{
}

HSpecTestWidget::~HSpecTestWidget()
{
}

void HSpecTestWidget::start()
{
    Q_D(HSpecTestWidget);
    HTestWidget::start();
    if (d->memento)
        d->memento->restore();
}

void HSpecTestWidget::stop()
{
    Q_D(HSpecTestWidget);
    HTestWidget::stop();
    if (d->memento)
        d->memento->save();
}

void HSpecTestWidget::init()
{
    Q_D(HSpecTestWidget);
    readSettings();
    HTestWidget::init();
    d->testResult = new HTestResult(this);
    d->testResult->setExportTypes(d->displays);
    d->testResult->setExportPathName(d->exportPathName);
    d->testResult->setSyncFileName(d->syncFileName);
    d->timer = new QTimer(this);
    d->timer->setInterval(d->syncInterval * 1000);
    connect(d->timer, &QTimer::timeout, this, [=] { d->testResult->syncFile(); });
    resetGrade();
}

void HSpecTestWidget::closeEvent(QCloseEvent *event)
{
    Q_D(HSpecTestWidget);
    stop();
    if (d->memento)
        d->memento->writeFile();
    if (!d->testResult->isEmpty())
    {
        if (QMessageBox::question(this, tr("保存数据"), tr("是否保存到数据库？")) == QMessageBox::Yes)
            d->testResult->exportDatabaseAll();
    }
    clearResult();
    if (d->cieDialog != nullptr)
        d->cieDialog->close();
    writeSettings();
    event->accept();
}

void HSpecTestWidget::handleAction(HActionType action)
{
    Q_D(HSpecTestWidget);
    if (action >= 0xF0000000)
    {
        setTest(false);
        clearResult();
        if (action == ACT_RESET_SPECTRUM)
            d->energyWidget->initCoordinate();
        if (action == ACT_RESET_CHROMATISM)
            d->chromatismWidget->initMenuShow();
        if (action == ACT_RESET_GRADE)
            resetGrade();
        return;
    }
    HAbstractTestWidget::handleAction(action);
}

void HSpecTestWidget::createAction()
{
    Q_D(HSpecTestWidget);
    HTestWidget::createAction();
    d->actionPrintPreviewLast = new QAction(tr("打印预览(&V)"), this);
    d->actionPrintPreviewLast->setIcon(QIcon(":/image/PrintPreview.png"));
    d->actionPrintPreviewLast->setIconText(tr("打印预览"));
    d->actionPrintPreviewLast->setEnabled(false);
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
    connect(d->actionPrintPreviewLast, &QAction::triggered, d->testResult, &ITestResult::printPreviewLast);
    connect(d->actionExportDatabaseLast, &QAction::triggered, d->testResult, &ITestResult::exportDatabaseLast);
    connect(d->actionExportDatabase, &QAction::triggered, this, &HSpecTestWidget::exportDatabase);
    connect(d->actionRemove, &QAction::triggered, this, &HSpecTestWidget::removeResult);
    connect(d->actionAdjust, &QAction::triggered, this, [=](bool b){ d->testData->setData("[使用调整]", b); });
    connect(d->actionExportPath, &QAction::triggered, this, &HSpecTestWidget::setExportPath);
    connect(d->actionSyncFile, &QAction::triggered, this, &HSpecTestWidget::setSyncFile);
}

void HSpecTestWidget::createWidget()
{
    Q_D(HSpecTestWidget);
    d->energyWidget = new HSpecEnergyWidget;
    d->cieWidget = new HCie1931Widget;
    d->chromatismWidget = new HSpecChromatismChartView;
    d->tableWidget = new HResultTableWidget;
}

void HSpecTestWidget::createMenu()
{
    Q_D(HSpecTestWidget);
    auto menu = new QMenu(tr("测试配置(&T)"));
    menu->addAction(d->actionAdjust);
    menu->addAction(d->actionExportPath);
    menu->addAction(d->actionSyncFile);
    d->menus << menu;
}

void HSpecTestWidget::createToolBar()
{
    Q_D(HSpecTestWidget);
    auto toolBar1 = new QToolBar(tr("设置(&S)"));
    auto toolBar2 = new QToolBar(tr("操作(&O)"));
    toolBar1->addWidget(d->testSetWidget);
    toolBar2->addAction(d->actionStart);
    toolBar2->addAction(d->actionStop);
    toolBar2->addAction(d->actionClear);
    toolBar2->addAction(d->actionExportExcel);
    toolBar2->addAction(d->actionExportDatabaseLast);
    toolBar2->addAction(d->actionPrintPreviewLast);
    d->toolBars << toolBar1 << toolBar2;
}

void HSpecTestWidget::initWidget()
{
    Q_D(HSpecTestWidget);
    auto layout = new QGridLayout(this);
    auto tabWidget1 = new QTabWidget;
    auto tabWidget2 = new QTabWidget;
    auto tabWidget3 = new QTabWidget;
    auto splitter1 = new QSplitter(Qt::Horizontal);
    auto splitter2 = new QSplitter(Qt::Vertical);
    d->tableWidget->setDisplay(d->displays);
    d->tableWidget->setSelected(d->tableSelecteds);
    d->tableWidget->addAction(d->actionClear);
    d->tableWidget->addAction(d->actionRemove);
    d->tableWidget->addAction(d->actionExportDatabase);
    tabWidget1->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    tabWidget1->addTab(d->energyWidget, d->energyWidget->windowTitle());
    tabWidget2->addTab(d->cieWidget, d->cieWidget->windowTitle());
    tabWidget2->addTab(d->chromatismWidget, d->chromatismWidget->windowTitle());
    tabWidget3->addTab(d->detailWidget, tr("当次结果"));
    tabWidget3->addTab(d->tableWidget, tr("结果列表"));
    splitter1->addWidget(tabWidget1);
    splitter1->addWidget(tabWidget2);
    splitter1->setHandleWidth(15);
    splitter1->setStretchFactor(0, 2);
    splitter1->setStretchFactor(1, 1);
    splitter2->addWidget(splitter1);
    splitter2->addWidget(tabWidget3);
    splitter2->setHandleWidth(15);
    splitter2->setStretchFactor(1, 1);
    layout->addWidget(splitter2);
    connect(d->testSetWidget, &ITestSetWidget::testStateChanged, this, &HSpecTestWidget::handleStateChanged);
    connect(d->testSetWidget, &ITestSetWidget::saveModeChanged, this, &HSpecTestWidget::handleSaveModeChanged);
    connect(d->testSetWidget, &ITestSetWidget::resultChanged, this, &HSpecTestWidget::handleResultChanged);
    connect(d->cieWidget, &HCie1931Widget::mouseDoubleClicked, this, &HSpecTestWidget::openCieDialog);
}

void HSpecTestWidget::exportExcel()
{
    Q_D(HSpecTestWidget);
    d->testResult->exportExcelLast();
}

void HSpecTestWidget::clearResult()
{
    Q_D(HSpecTestWidget);
    d->testResult->clear();
    d->cieWidget->clearPoint();
    d->tableWidget->clearResult();
}

void HSpecTestWidget::readSettings()
{
    Q_D(HSpecTestWidget);
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup("TestWidget");
    d->tableSelecteds = settings->value("TableSelected", d->displays).toStringList();
    d->exportPathName = settings->value("ExportPathName", ".").toString();
    d->syncFileName = settings->value("SyncFileName", "aaa.tmp").toString();
    d->syncInterval = settings->value("SyncInterval", 20).toInt();
    d->testData->setData("[使用调整]", settings->value("Adjust", false));
    d->testData->setData("[CCD偏差]", settings->value("Offset", 55.0));
    settings->endGroup();
}

void HSpecTestWidget::writeSettings()
{
    Q_D(HSpecTestWidget);
    if (!d->modified)
        return;
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup("TestWidget");
    settings->setValue("TableSelected", d->tableWidget->selected());
    settings->setValue("ExportPathName", d->exportPathName);
    settings->setValue("SyncFileName", d->syncFileName);
    settings->setValue("SyncInterval", d->syncInterval);
    settings->setValue("Adjust", d->testData->data("[使用调整]"));
    settings->setValue("Offset", d->testData->data("[CCD偏差]"));
    settings->endGroup();
    d->modified = false;
}

void HSpecTestWidget::postProcess()
{
    Q_D(HSpecTestWidget);
    d->configManage->postProcess(d->testData, d->displays);
    d->testData->setData("[测量日期时间]", QDateTime::currentDateTime());
}

void HSpecTestWidget::refreshWidget(bool append)
{
    Q_D(HSpecTestWidget);
    auto point = d->testData->data("[色坐标]").toPointF();
    d->energyWidget->refreshWidget();
    d->detailWidget->refreshWidget();
    d->chromatismWidget->refreshWidget();
    d->tableWidget->refreshResult(append);
    if (append)
    {
        d->cieWidget->addPoint(point);
        if (d->cieWidget2 != nullptr)
            d->cieWidget2->addPoint(point);
    }
    else
    {
        d->cieWidget->setPointFocus(point);
        if (d->cieWidget2 != nullptr)
            d->cieWidget2->setPointFocus(point);
    }
}

void HSpecTestWidget::handleStateChanged(bool b)
{
    Q_D(HSpecTestWidget);
    d->actionStart->setEnabled(!b);
    d->actionStop->setEnabled(b);
    d->actionClear->setEnabled(!b);
    d->actionPrintPreviewLast->setEnabled(!b);
    d->actionExportExcel->setEnabled(!b);
    d->actionExportDatabase->setEnabled(!b);
    d->actionExportDatabaseLast->setEnabled(!b);
}

void HSpecTestWidget::handleSaveModeChanged(int value)
{
    Q_D(HSpecTestWidget);
    if (value == 2)
        d->timer->start();
    else
        d->timer->stop();
}

void HSpecTestWidget::handleResultChanged(HActionType, bool append)
{
    Q_D(HSpecTestWidget);
    postProcess();
    refreshWidget(append);
    d->testResult->save(append);
    if (d->testSetWidget->saveMode() == 1)
    {
        if (append)
            d->testResult->exportExcelAppend();
    }
    if (d->testSetWidget->saveMode() == 2)
        d->timer->start();
}

void HSpecTestWidget::openCieDialog()
{
    Q_D(HSpecTestWidget);
    if (d->cieWidget2 == nullptr)
    {
        d->cieWidget2 = new HCie1931Widget;
        d->cieDialog = HGuiHelper::decoratorInDialog(d->cieWidget2, this);
    }
    d->cieDialog->show();
}

void HSpecTestWidget::resetGrade()
{
    Q_D(HSpecTestWidget);
    auto p = d->configManage->gradeCollection()->levels("[色坐标]").value<QList<QPolygonF>>();
    d->cieWidget->setGrade(p);
    if (d->cieWidget2 != nullptr)
        d->cieWidget2->setGrade(p);
}

void HSpecTestWidget::exportDatabase()
{
    Q_D(HSpecTestWidget);
    for (const auto &range : d->tableWidget->selectedRanges())
        d->testResult->exportDatabase(range.topRow(), range.rowCount());
}

void HSpecTestWidget::removeResult()
{
    Q_D(HSpecTestWidget);
    auto ranges = d->tableWidget->selectedRanges();
    for (const auto &range : ranges)
    {
        d->testResult->remove(range.topRow(), range.rowCount());
        d->tableWidget->removeRows(range.topRow(), range.rowCount());
    }
}

void HSpecTestWidget::setExportPath()
{
    Q_D(HSpecTestWidget);
    d->exportPathName = QFileDialog::getExistingDirectory(this, tr("导出目录"), ".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    d->testResult->setExportPathName(d->exportPathName);
}

void HSpecTestWidget::setSyncFile()
{
    Q_D(HSpecTestWidget);
    d->exportPathName = QFileDialog::getSaveFileName(this, tr("同步文件"));
    d->testResult->setSyncFileName(d->exportPathName);
}

HE_GUI_END_NAMESPACE
