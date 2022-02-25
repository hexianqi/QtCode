#include "HSpecTestWidget_p.h"
#include "HGuiHelper.h"
#include "ITestDetailWidget.h"
#include "ITestSetWidget.h"
#include "HTestResult.h"
#include "HSpecEnergyWidget.h"
#include "HSpecChromatismChartView.h"
#include "HResultTableWidget.h"
#include "HProductEditDialog.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IGradeCollection.h"
#include "HeData/ITestData.h"
#include "HeData/IPrint.h"
#include "HeData/IPrintTemplate.h"
#include "HeData/ITextExport.h"
#include "HeData/ITextExportTemplate.h"
#include "HeController/IMementoCollection.h"
#include "HePlugin/HCie1931Widget.h"
#include "HePlugin/HTm30BarChart.h"
#include "HePlugin/HTm30CvgWidget.h"
#include "HePlugin/HTm30GamutWidget.h"
#include "HePlugin/HTm30SpdChartView.h"
#include "HePlugin/HTm30RfRgChartView.h"
#include "HePlugin/HTm30RfiChartView.h"
#include "HePlugin/HTm30RfhjChartView.h"
#include "HePlugin/HTm30RcshjChartView.h"
#include "HePlugin/HTm30RhshjChartView.h"
#include "HeSql/ISqlHandle.h"
#include "HeSql/HSql.h"
#include <QtCore/QDateTime>
#include <QtCore/QSettings>
#include <QtCore/QTimer>
#include <QtGui/QCloseEvent>
#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QSplitter>

HE_BEGIN_NAMESPACE

HSpecTestWidgetPrivate::HSpecTestWidgetPrivate()
{
    auto mementoCollection = HAppContext::getContextPointer<IMementoCollection>("IMementoCollection");
    memento = mementoCollection->value("Spec");
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
    sqlHandle = HAppContext::getContextPointer<ISqlHandle>("ISqlHandle");
    print = HAppContext::getContextPointer<IPrint>("IPrint");
    specPrintTemplate = HAppContext::getContextPointer<IPrintTemplate>("ISpecPrintTemplate");
    tagPrintTemplate = HAppContext::getContextPointer<IPrintTemplate>("ITagPrintTemplate");
    textExport = HAppContext::getContextPointer<ITextExport>("ITextExport");
    specTextTemplate = HAppContext::getContextPointer<ITextExportTemplate>("ISpecTextExportTemplate");
}

HSpecTestWidget::HSpecTestWidget(QWidget *parent) :
    HTestWidget(*new HSpecTestWidgetPrivate, parent)
{
    init();
}

HSpecTestWidget::HSpecTestWidget(HSpecTestWidgetPrivate &p, QWidget *parent) :
    HTestWidget(p, parent)
{
}

HSpecTestWidget::~HSpecTestWidget()
{
}

void HSpecTestWidget::init()
{
    Q_D(HSpecTestWidget);
    readSettings();
    d->testResult = new HTestResult(this);
    d->testResult->setSyncType(d->displays);
    d->testResult->setSyncFile(d->syncFile);
    d->textExport->setExportPath(d->exportPath);
    d->timer = new QTimer(this);
    d->timer->setInterval(d->syncInterval * 1000);
    connect(d->timer, &QTimer::timeout, this, [=] { d->testResult->syncFile(); });
    HTestWidget::init();
    resetGrade();
}

void HSpecTestWidget::closeEvent(QCloseEvent *event)
{
    Q_D(HSpecTestWidget);
    stop();
    if (!d->testResult->isEmpty() && QMessageBox::question(this, tr("保存数据"), tr("是否保存到数据库？")) == QMessageBox::Yes)
        exportDatabaseRange(0, d->testResult->size());
    clearResult();
    if (d->cieDialog)
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
            resetSpec();
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
    d->actionPrintPreview = new QAction(tr("打印预览(&V)"), this);
    d->actionPrintPreview->setIcon(QIcon(":/image/PrintPreview.png"));
    d->actionPrintPreview->setIconText(tr("打印预览"));
    d->actionPrintPreview->setEnabled(false);
    d->actionPrintTag = new QAction(tr("打印标签(&T)"), this);
    d->actionPrintTag->setIcon(QIcon(":/image/Tag.png"));
    d->actionPrintTag->setVisible(d->tagPrintTemplate != nullptr);
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
    d->actionProductEidt = new QAction(tr("产品信息修改(&P)"), this);
    d->actionProductEidt->setVisible(d->productEditable);
    connect(d->actionPrintPreview, &QAction::triggered, this, &HSpecTestWidget::printPreview);
    connect(d->actionPrintTag, &QAction::triggered, this, &HSpecTestWidget::printTag);
    connect(d->actionExportDatabaseLast, &QAction::triggered, this, &HSpecTestWidget::exportDatabaseLast);
    connect(d->actionExportDatabase, &QAction::triggered, this, &HSpecTestWidget::exportDatabase);
    connect(d->actionRemove, &QAction::triggered, this, &HSpecTestWidget::removeResult);
    connect(d->actionAdjust, &QAction::triggered, this, [=](bool b){ d->testData->setData("[使用调整]", b); });
    connect(d->actionExportPath, &QAction::triggered, this, &HSpecTestWidget::setExportPath);
    connect(d->actionSyncFile, &QAction::triggered, this, &HSpecTestWidget::setSyncFile);
    connect(d->actionProductEidt, &QAction::triggered, this, &HSpecTestWidget::editProduct);
}

void HSpecTestWidget::createWidget()
{
    Q_D(HSpecTestWidget);
    d->cieWidget = new HCie1931Widget;
    d->spdWidget = new HTm30SpdChartView;
    d->cvgWidget = new HTm30CvgWidget;
    d->gamutWidget = new HTm30GamutWidget;
    d->rfrgWidget = new HTm30RfRgChartView;
    d->rfiWidget = new HTm30RfiChartView;
    d->rfhjWidget = new HTm30RfhjChartView;
    d->rcshjWidget = new HTm30RcshjChartView;
    d->rhshjWidget = new HTm30RhshjChartView;
    d->energyWidget = new HSpecEnergyWidget;
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
    toolBar2->addAction(d->actionPrintPreview);
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
    d->tableWidget->addAction(d->actionProductEidt);
    d->tableWidget->addAction(d->actionExportDatabase);
    d->tableWidget->addAction(d->actionPrintTag);
    tabWidget1->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    tabWidget1->addTab(d->energyWidget, d->energyWidget->windowTitle());
    tabWidget1->addTab(d->spdWidget, tr("相对光谱功率分布2"));
    tabWidget1->addTab(d->rfiWidget, d->rfiWidget->windowTitle());
    tabWidget1->addTab(d->rfhjWidget, d->rfhjWidget->windowTitle());
    tabWidget1->addTab(d->rcshjWidget, d->rcshjWidget->windowTitle());
    tabWidget1->addTab(d->rhshjWidget, d->rhshjWidget->windowTitle());
    tabWidget2->addTab(d->cieWidget, d->cieWidget->windowTitle());
    tabWidget2->addTab(d->chromatismWidget, d->chromatismWidget->windowTitle());
    tabWidget2->addTab(d->cvgWidget, d->cvgWidget->windowTitle());
    tabWidget2->addTab(d->gamutWidget, d->gamutWidget->windowTitle());
    tabWidget2->addTab(d->rfrgWidget, d->rfrgWidget->windowTitle());
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
    connect(d->tableWidget, &HResultTableWidget::itemDoubleClicked, this, &HSpecTestWidget::editProduct);
}

void HSpecTestWidget::clearResult()
{
    Q_D(HSpecTestWidget);
    d->testResult->clear();
    d->textExport->clear();
    d->cieWidget->clearPoint();
    d->tableWidget->clearResult();
}

void HSpecTestWidget::exportExcel()
{
    Q_D(HSpecTestWidget);
    auto data = d->testResult->last();
    if (data == nullptr)
        return;

    auto type = QStringList() << d->displays << "[光谱能量曲线]";
    d->specTextTemplate->setDataType(type);
    d->specTextTemplate->setData(data->select(type));
    d->textExport->setTextTemplate(d->specTextTemplate);
    d->textExport->saveAs();
}

void HSpecTestWidget::readSettings()
{
    Q_D(HSpecTestWidget);
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("TestWidget");
    d->tableSelecteds = settings->value("TableSelected", d->displays).toStringList();
    d->exportPath = settings->value("ExportPath", ".").toString();
    d->syncFile = settings->value("SyncFile", "temp.xlsx").toString();
    d->syncInterval = settings->value("SyncInterval", 20).toInt();
    d->testData->setData("[使用调整]", settings->value("Adjust", false));
    d->testData->setData("[CCD偏差]", settings->value("Offset", 55.0));
    settings->endGroup();
    d->testData->handleOperation("<读取配置>", fileName);
}

void HSpecTestWidget::writeSettings()
{
    Q_D(HSpecTestWidget);
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("TestWidget");
    settings->setValue("TableSelected", d->tableWidget->selected());
    settings->setValue("ExportPath", d->exportPath);
    settings->setValue("SyncFile", d->syncFile);
    settings->setValue("SyncInterval", d->syncInterval);
    settings->setValue("Adjust", d->testData->data("[使用调整]"));
    settings->setValue("Offset", d->testData->data("[CCD偏差]"));
    settings->endGroup();
    d->testData->handleOperation("<写入配置>", fileName);
}

void HSpecTestWidget::postProcess(bool append)
{
    Q_D(HSpecTestWidget);
    d->configManage->postProcess(d->testData, d->displays);
    d->testData->setData("[测量日期时间]", QDateTime::currentDateTime());
    if (append)
        d->testData->handleOperation("<编号自增>");
}

void HSpecTestWidget::refreshWidget(bool append)
{
    Q_D(HSpecTestWidget);
    auto point = d->testData->data("[色坐标]").toPointF();
    d->energyWidget->refreshWidget();
    d->chromatismWidget->refreshWidget();
    d->detailWidget->refreshWidget();
    d->tableWidget->refreshResult(append);
    if (append)
    {
        d->cieWidget->addPoint(point);
        if (d->cieWidget2)
            d->cieWidget2->addPoint(point);
    }
    else
    {
        d->cieWidget->setPointFocus(point);
        if (d->cieWidget2)
            d->cieWidget2->setPointFocus(point);
    }
    d->spdWidget->setTest(d->testData->data("[光谱能量曲线]").value<QPolygonF>());
    d->spdWidget->setReference(d->testData->data("[光谱反射曲线]").value<QPolygonF>());
    d->cvgWidget->setData(d->testData->select(d->cvgWidget->dataType()));
    d->gamutWidget->setData(d->testData->select(d->gamutWidget->dataType()));
    d->rfrgWidget->setRfRg(d->testData->data("[TM30_Rf]").toDouble(), d->testData->data("[TM30_Rg]").toDouble());
    d->rfiWidget->chart()->setBarValue(d->testData->data("[TM30_Rfi]").value<QList<double>>());
    d->rfhjWidget->chart()->setBarValue(d->testData->data("[TM30_hj_Rf]").value<QList<double>>());
    d->rcshjWidget->chart()->setBarValue(d->testData->data("[TM30_hj_Rcs]").value<QList<double>>());
    d->rhshjWidget->chart()->setBarValue(d->testData->data("[TM30_hj_Rhs]").value<QList<double>>());
}

void HSpecTestWidget::handleStateChanged(bool b)
{
    Q_D(HSpecTestWidget);
    d->actionStart->setEnabled(!b);
    d->actionStop->setEnabled(b);
    d->actionClear->setEnabled(!b);
    d->actionPrintPreview->setEnabled(!b);
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
    postProcess(append);
    refreshWidget(append);
    d->testResult->update(append);
    if (d->testSetWidget->saveMode() == 1 && append)
        exportExcelAppend();
}

void HSpecTestWidget::exportExcelAppend()
{
    Q_D(HSpecTestWidget);
    auto data = d->testResult->last();
    if (data == nullptr)
        return;

    d->specTextTemplate->setDataType(d->displays);
    d->specTextTemplate->setData(data->select(d->displays));
    d->textExport->setTextTemplate(d->specTextTemplate);
    d->textExport->append();
}

void HSpecTestWidget::exportDatabase()
{
    Q_D(HSpecTestWidget);
    for (const auto &range : d->tableWidget->selectedRanges())
        exportDatabaseRange(range.topRow(), range.rowCount());
}

void HSpecTestWidget::exportDatabaseRange(int index, int count)
{
    Q_D(HSpecTestWidget);
    if (d->testResult->isEmpty() || count < 1 || index < 0)
        return;

    auto field = d->sqlHandle->field();
    count = qMin(d->testResult->size() - index, count);
    for (int i = 0; i < count; i++)
    {
        auto record = HSql::toRecord(field, d->testResult->at(index + i));
        d->sqlHandle->addRecord(record);
    }
}

void HSpecTestWidget::exportDatabaseLast()
{
    Q_D(HSpecTestWidget);
    auto data = d->testResult->last();
    if (data == nullptr)
        return;
    auto record = HSql::toRecord(d->sqlHandle->field(), data);
    d->sqlHandle->addRecord(record);
}

void HSpecTestWidget::printPreview()
{
    Q_D(HSpecTestWidget);
    auto data = d->testResult->last();
    if (data == nullptr)
        return;
    d->specPrintTemplate->setData(data->select(d->specPrintTemplate->dataType()));
    d->print->setPrintTemplate(d->specPrintTemplate);
    d->print->printPreview();
}

void HSpecTestWidget::printTag()
{
    Q_D(HSpecTestWidget);
    auto row = d->tableWidget->currentRow();
    auto data = d->testResult->at(row);
    if (data == nullptr)
        return;

    d->tagPrintTemplate->setData(data->select(d->tagPrintTemplate->dataType()));
    d->print->setPrintTemplate(d->tagPrintTemplate);
    d->print->print();
}

void HSpecTestWidget::resetSpec()
{
    Q_D(HSpecTestWidget);
    auto point = d->testData->data("[光谱波长范围]").toPointF();
    d->energyWidget->initCoordinate();
    d->spdWidget->setAxisXRange(point.x(), point.y());
}

void HSpecTestWidget::resetGrade()
{
    Q_D(HSpecTestWidget);
    auto p = d->configManage->gradeCollection()->levels("[色坐标]").value<QList<QPolygonF>>();
    d->cieWidget->setGrade(p);
    if (d->cieWidget2)
        d->cieWidget2->setGrade(p);
}

void HSpecTestWidget::openCieDialog()
{
    Q_D(HSpecTestWidget);
    if (d->cieWidget2 == nullptr)
    {
        d->cieWidget2 = new HCie1931Widget;
        d->cieWidget2->setGrade(d->configManage->gradeCollection()->levels("[色坐标]").value<QList<QPolygonF>>());
        d->cieDialog = HGuiHelper::decoratorInDialog(d->cieWidget2, this);
    }
    d->cieDialog->show();
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
    d->exportPath = QFileDialog::getExistingDirectory(this, tr("导出目录"), ".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    d->textExport->setExportPath(d->exportPath);
}

void HSpecTestWidget::setSyncFile()
{
    Q_D(HSpecTestWidget);
    d->syncFile = QFileDialog::getSaveFileName(this, tr("同步文件"), ".", "Excel files (*.xlsx)");
    d->testResult->setSyncFile(d->syncFile);
}

void HSpecTestWidget::editProduct()
{
    Q_D(HSpecTestWidget);
    if (!d->productEditable)
        return;

    auto row = d->tableWidget->currentRow();
    auto data = d->testResult->at(row);
    HProductEditDialog dlg(this);
    dlg.setData(data);
    if (dlg.exec() != QDialog::Accepted)
        return;
    d->testResult->setModified();
    d->tableWidget->refreshResult(row, data);
}

HE_END_NAMESPACE
