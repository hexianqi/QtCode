#include "HTestWidget7000_p.h"
#include "HTestResult7000.h"
#include "HTestSetWidget7000.h"
#include "HDetailWidget7000.h"
#include "HLocationWidget.h"
#include "HeCore/HCore.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IGradeCollection.h"
#include "HeData/IQualityCollection.h"
#include "HeData/ILocationCollection.h"
#include "HeData/ITestData.h"
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
#include "HeGui/HSpecEnergyWidget.h"
#include "HeGui/HSpecChromatismChartView.h"
#include "HeGui/HResultTableWidget.h"
#include "HeGui/HProductEditDialog.h"
#include <QtCore/QSettings>
#include <QtGui/QCloseEvent>
#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSplitter>

HTestWidget7000Private::HTestWidget7000Private()
{
    auto group = QStringList() << "|时间信息2|" << "|产品信息3|" << "|环境信息|"  << "|直流电信息|" << "|光度信息|" << "|光谱信息5|" << "|色容差信息2|" << "|光合信息|" << "|TM30信息2|";
    auto mementoCollection = HAppContext::getContextPointer<IMementoCollection>("IMementoCollection");
    memento = mementoCollection->value("Spec");
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
    textExport = HAppContext::getContextPointer<ITextExport>("ITextExport");
    textTemplate = HAppContext::getContextPointer<ITextExportTemplate>("ISpecTextExportTemplate");
    displays = QStringList() << "[分级]" << HCore::membership(group);
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
    d->testResult = new HTestResult7000(this);
    HTestWidget::init();
    resetGrade();
    resetQuality();
    resetLocation();
    d->energyWidget->addProgressBar("[光采样比率]");
    setProbe(d->testData->data("[使用光探头]").toBool());
}

void HTestWidget7000::closeEvent(QCloseEvent *event)
{
    stop();
    writeSettings();
    event->accept();
}

void HTestWidget7000::handleAction(HActionType action)
{
    Q_D(HTestWidget7000);
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
        if (action == ACT_RESET_QUALITY)
            resetQuality();
        if (action == ACT_RESET_LOCATION)
            resetLocation();
        return;
    }
    HAbstractTestWidget::handleAction(action);
}

void HTestWidget7000::createAction()
{
    Q_D(HTestWidget7000);
    HTestWidget::createAction();
    d->actionAdjust = new QAction(tr("使用调整(&A)"), this);
    d->actionAdjust->setCheckable(true);
    d->actionAdjust->setChecked(d->testData->data("[使用调整]").toBool());
    d->actionProbe = new QAction(tr("使用光探头(&P)"), this);
    d->actionProbe->setCheckable(true);
    d->actionProbe->setChecked(d->testData->data("[使用光探头]").toBool());
    d->actionProductEidt = new QAction(tr("产品信息修改(&P)"), this);
    connect(d->actionAdjust, &QAction::triggered, this, [=](bool b){ d->testData->setData("[使用调整]", b); });
    connect(d->actionProbe, &QAction::triggered, this, &HTestWidget7000::setProbe);
    connect(d->actionProductEidt, &QAction::triggered, this, &HTestWidget7000::editProduct);
}

void HTestWidget7000::createWidget()
{
    Q_D(HTestWidget7000);
    d->cieWidget = new HCie1931Widget;
    d->energyWidget = new HSpecEnergyWidget;
    d->chromatismWidget = new HSpecChromatismChartView;
    d->tableWidget = new HResultTableWidget;
    d->locationWidget = new HLocationWidget;
    d->testSetWidget = new HTestSetWidget7000;
    d->detailWidget = new HDetailWidget7000;
}

void HTestWidget7000::createMenu()
{
    Q_D(HTestWidget7000);
    auto menu = new QMenu(tr("测试配置(&T)"));
    menu->addAction(d->actionAdjust);
    menu->addAction(d->actionProbe);
    d->menus << menu;
}

void HTestWidget7000::createToolBar()
{
    Q_D(HTestWidget7000);
    auto toolBar1 = new QToolBar(tr("设置(&S)"));
    auto toolBar2 = new QToolBar(tr("操作(&O)"));
    toolBar1->addWidget(d->testSetWidget);
    toolBar2->addAction(d->actionStart);
    toolBar2->addAction(d->actionStop);
    toolBar2->addAction(d->actionClear);
    toolBar2->addAction(d->actionExportExcel);
    d->toolBars << toolBar1 << toolBar2;
}

void HTestWidget7000::initWidget()
{
    Q_D(HTestWidget7000);
    auto layout = new QGridLayout(this);
    auto tabWidget1 = new QTabWidget;
    auto tabWidget2 = new QTabWidget;
    auto splitter1 = new QSplitter(Qt::Horizontal);
    auto splitter2 = new QSplitter(Qt::Vertical);
    d->tableWidget->setDisplay(d->displays);
    d->tableWidget->setSelected(d->tableSelecteds);
    d->tableWidget->addAction(d->actionClear);
    d->tableWidget->addAction(d->actionProductEidt);
    splitter1->addWidget(d->energyWidget);
    splitter1->addWidget(tabWidget2);
    splitter1->setHandleWidth(15);
    splitter1->setStretchFactor(0, 2);
    splitter1->setStretchFactor(1, 1);
    splitter2->addWidget(splitter1);
    splitter2->addWidget(d->detailWidget);
    splitter2->setHandleWidth(15);
    splitter2->setStretchFactor(1, 1);
    tabWidget1->addTab(d->locationWidget,   tr("结果图表"));
    tabWidget1->addTab(d->tableWidget,      tr("结果列表"));
    tabWidget1->addTab(splitter2,           tr("当次结果"));
    tabWidget2->addTab(d->cieWidget,        d->cieWidget->windowTitle());
    tabWidget2->addTab(d->chromatismWidget, d->chromatismWidget->windowTitle());
    layout->addWidget(tabWidget1);
    connect(d->testSetWidget, &ITestSetWidget::testStateChanged, this, &HTestWidget7000::handleStateChanged);
    connect(d->testSetWidget, &ITestSetWidget::saveModeChanged, this, &HTestWidget7000::handleSaveModeChanged);
    connect(d->testSetWidget, &ITestSetWidget::resultChanged, this, &HTestWidget7000::handleResultChanged);
    connect(d->tableWidget, &HResultTableWidget::itemDoubleClicked, this, &HTestWidget7000::editProduct);
}

void HTestWidget7000::clearResult()
{
    Q_D(HTestWidget7000);
    d->testResult->clear();
    d->textExport->clear();
    d->cieWidget->clearPoint();
    d->tableWidget->clearResult();
    d->locationWidget->clearResult();
}

void HTestWidget7000::exportExcel()
{
    Q_D(HTestWidget7000);
    if (d->testResult->isEmpty())
        return;

    QVariantList list;
    for (int i = 0; i < d->testResult->size(); i++)
        list << d->testResult->at(i)->select(d->displays);
    d->textTemplate->setDataType(d->displays);
    d->textTemplate->setData(list);
    d->textExport->setTextTemplate(d->textTemplate);
    d->textExport->saveAs();
}

void HTestWidget7000::readSettings()
{
    Q_D(HTestWidget7000);
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("TestWidget");
    d->tableSelecteds = settings->value("TableSelected", d->displays).toStringList();
    d->testData->setData("[使用调整]", settings->value("Adjust", false));
    d->testData->setData("[CCD偏差]", settings->value("Offset", 55.0));
    d->testData->setData("[使用光探头]", settings->value("Probe", false));
    settings->endGroup();
    d->testData->handleOperation("<读取配置>", fileName);
}

void HTestWidget7000::writeSettings()
{
    Q_D(HTestWidget7000);
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("TestWidget");
    settings->setValue("TableSelected", d->tableWidget->selected());
    settings->setValue("Adjust", d->testData->data("[使用调整]"));
    settings->setValue("Offset", d->testData->data("[CCD偏差]"));
    settings->setValue("Probe", d->testData->data("[使用光探头]"));
    settings->endGroup();
    d->testData->handleOperation("<写入配置>", fileName);
}

void HTestWidget7000::handleStateChanged(bool b)
{
    Q_D(HTestWidget7000);
    d->actionStart->setEnabled(!b);
    d->actionStop->setEnabled(b);
    d->actionClear->setEnabled(!b);
    d->actionExportExcel->setEnabled(!b);
}

void HTestWidget7000::handleSaveModeChanged(int)
{

}

void HTestWidget7000::handleResultChanged(HActionType, bool)
{

}

void HTestWidget7000::resetGrade()
{
    Q_D(HTestWidget7000);
    d->cieWidget->setGrade(d->configManage->gradeCollection()->levels("[色坐标]").value<QList<QPolygonF>>());
}

void HTestWidget7000::resetQuality()
{
    Q_D(HTestWidget7000);
    auto qc = d->configManage->qualityCollection();
    d->locationWidget->setColor(qc->color(HQualityReport::InvalidData), qc->color(HQualityReport::Spacer));
}

void HTestWidget7000::resetLocation()
{
    Q_D(HTestWidget7000);
    auto polygon = d->configManage->locationCollection()->polygon();
    if (d->polygon == polygon)
        return;
    d->polygon = polygon;
    d->locationWidget->setPolygon(polygon);
    d->tableWidget->setFixedRowCount(polygon.size());
    d->testSetWidget->handleOperation("<设置布局>", polygon);
}

void HTestWidget7000::setProbe(bool b)
{
    Q_D(HTestWidget7000);
    d->testData->setData("[使用光探头]", b);
    d->energyWidget->setProgressBarVisible("[光采样比率]", b);
    d->testSetWidget->handleOperation("<启用光挡位>", b);
}

void HTestWidget7000::editProduct()
{
    Q_D(HTestWidget7000);
    auto row = d->tableWidget->currentRow();
    auto data = d->testResult->at(row);
    HProductEditDialog dlg(this);
    dlg.setData(data);
    if (dlg.exec() != QDialog::Accepted)
        return;
    d->testResult->setModified();
    d->tableWidget->refreshResult(row, data);
}
