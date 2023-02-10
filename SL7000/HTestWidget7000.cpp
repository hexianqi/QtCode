#include "HTestWidget7000_p.h"
#include "HTestResult7000.h"
#include "HTestSetWidget7000.h"
#include "HDetailWidget7000.h"
#include "HLocationWidget.h"
#include "HeCore/HCore.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IGradeCollection.h"
#include "HeData/IGrade.h"
#include "HeData/IGradeItem.h"
#include "HeData/IQualityCollection.h"
#include "HeData/ILocationCollection.h"
#include "HeData/ITestData.h"
#include "HeData/ITextExport.h"
#include "HeData/ITextExportTemplate.h"
#include "HeController/IModel.h"
#include "HeController/IMementoCollection.h"
#include "HePlugin/HCie1931Widget.h"
#include "HeGui/HSpecEnergyWidget.h"
#include "HeGui/HSpecChromatismChartView.h"
#include "HeGui/HResultTableWidget.h"
#include "HeGui/HProductEditDialog.h"
#include <QtCore/QSettings>
#include <QtCore/QDateTime>
#include <QtGui/QCloseEvent>
#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QFileDialog>

HTestWidget7000Private::HTestWidget7000Private()
{
    auto group = QStringList() << "|时间信息2|" << "|产品信息3|" << "|环境信息|"  << "|直流电信息|" << "|光度信息2|" << "|光谱信息5|" << "|色容差信息2|" << "|光合信息|" << "|TM30信息2|";
    auto mementos = HAppContext::getContextPointer<IMementoCollection>("IMementoCollection");
    memento = mementos->value("Spec");
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
    textExport = HAppContext::getContextPointer<ITextExport>("ITextExport");
    textTemplate = HAppContext::getContextPointer<ITextExportTemplate>("ISpecTextExportTemplate");
    model = HAppContext::getContextPointer<IModel>("IModel");
    displays = QStringList() << "[电机定位]" << "[分级]" << HCore::membership(group);
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
    HTestWidget::init();
    d->testResult = new HTestResult7000(this);
    d->textExport->setExportPath(d->exportPath);
    resetGrade();
    resetQuality();
    resetLocation();
    setProbe(d->testData->data("[使用光探头]").toBool());
}

void HTestWidget7000::handleAction(HActionType action)
{
    Q_D(HTestWidget7000);
    if (action == ACT_SET_MOTOR_LOCATION)
    {
        auto point = d->testData->data("[电机定位]").toPoint();
        d->index = d->polygon.indexOf(point);
    }
    if (action == ACT_QUERY_NEXT_TEST)
    {
        d->index2 = next(d->index2);
        if (d->index2 >= 0)
        {
            d->testData->setData("[电机定位]", d->polygon.at(d->index2));
            d->model->addAction(ACT_SET_MOTOR_LOCATION);
        }
        else
            setTest(false);
        return;
    }
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
    d->actionExportPath = new QAction(tr("配置导出目录(&D)"), this);
    d->actionAdjust = new QAction(tr("使用调整(&A)"), this);
    d->actionAdjust->setCheckable(true);
    d->actionAdjust->setChecked(d->testData->data("[使用调整]").toBool());
    d->actionProbe = new QAction(tr("使用光探头(&P)"), this);
    d->actionProbe->setCheckable(true);
    d->actionProbe->setChecked(d->testData->data("[使用光探头]").toBool());
    d->actionProductEidt = new QAction(tr("产品信息修改(&P)"), this);
    connect(d->actionExportPath, &QAction::triggered, this, &HTestWidget7000::setExportPath);
    connect(d->actionAdjust, &QAction::triggered, this, [=](bool b){ d->testData->setData("[使用调整]", b); });
    connect(d->actionProbe, &QAction::triggered, this, &HTestWidget7000::setProbe);
    connect(d->actionProductEidt, &QAction::triggered, this, &HTestWidget7000::editProduct);
}

void HTestWidget7000::createWidget()
{
    Q_D(HTestWidget7000);
    d->cieWidget = new HCie1931Widget;
    d->energyWidget = new HSpecEnergyWidget;
    d->energyWidget->addProgressBar("[光采样比率]");
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
    menu->addAction(d->actionExportPath);
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
//    connect(d->testSetWidget, &ITestSetWidget::testStateChanged, this, &HTestWidget7000::handleStateChanged);
//    connect(d->testSetWidget, &ITestSetWidget::resultChanged, this, &HTestWidget7000::handleResultChanged);
    connect(d->testSetWidget, SIGNAL(testStateChanged(bool)), this, SLOT(handleStateChanged(bool)));
    connect(d->testSetWidget, SIGNAL(resultChanged(HActionType, bool)), this, SLOT(handleResultChanged(HActionType, bool)));
    connect(d->tableWidget, &HResultTableWidget::itemDoubleClicked, this, &HTestWidget7000::editProduct);
}

void HTestWidget7000::clearResult()
{
    Q_D(HTestWidget7000);
    d->index2 = -1;
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
    {
        if (d->testResult->at(i))
            list << d->testResult->at(i)->select(d->displays);
    }
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
    settings->beginGroup("SpecTestWidget");
    d->tableSelecteds = settings->value("TableSelected", d->displays).toStringList();
    d->exportPath = settings->value("ExportPath", ".").toString();
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
    settings->beginGroup("SpecTestWidget");
    settings->setValue("TableSelected", d->tableWidget->selected());
    settings->setValue("ExportPath", d->exportPath);
    settings->setValue("Adjust", d->testData->data("[使用调整]"));
    settings->setValue("Offset", d->testData->data("[CCD偏差]"));
    settings->setValue("Probe", d->testData->data("[使用光探头]"));
    settings->endGroup();
    d->testData->handleOperation("<写入配置>", fileName);
}

void HTestWidget7000::handleStateChanged(bool b)
{
    Q_D(HTestWidget7000);
    d->index2 = -1;
    d->actionStart->setEnabled(!b);
    d->actionStop->setEnabled(b);
    d->actionClear->setEnabled(!b);
    d->actionExportExcel->setEnabled(!b);
}

void HTestWidget7000::handleResultChanged(HActionType, bool)
{
    Q_D(HTestWidget7000);
    postProcess();
    refreshWidget();
    d->testResult->update();
}

void HTestWidget7000::postProcess()
{
    Q_D(HTestWidget7000);
    d->configManage->processAll(d->testData, d->displays, "Spec");
    d->testData->setData("[测量日期时间]", QDateTime::currentDateTime());
    d->testData->handleOperation("<编号自增>");
}

void HTestWidget7000::refreshWidget()
{
    Q_D(HTestWidget7000);
    auto point = d->testData->data("[色坐标]").toPointF();
    d->energyWidget->refreshWidget();
    d->chromatismWidget->refreshWidget();
    d->detailWidget->refreshWidget();
    d->locationWidget->refreshResult();
    d->tableWidget->refreshRow(d->index);
    d->cieWidget->addPoint(point);
}

void HTestWidget7000::resetGrade()
{
    Q_D(HTestWidget7000);

    auto grade = d->configManage->gradeCollection()->useItem();
    if (grade != nullptr && grade->contains("[色坐标]"))
    {
        auto item = grade->item("[色坐标]");
        d->cieWidget->setGrade(item->levels().value<QList<QPolygonF>>());
        d->cieWidget->setGradeName(item->data("[名称]").toStringList());
    }
}

void HTestWidget7000::resetQuality()
{
    Q_D(HTestWidget7000);
    auto qc = d->configManage->qualityCollection("Spec");
    d->locationWidget->setColor(qc->color(HQualityReport::InvalidData), qc->color(HQualityReport::Spacer));
}

void HTestWidget7000::resetLocation()
{
    Q_D(HTestWidget7000);
    auto polygon = d->configManage->locationCollection()->polygon();
    if (d->polygon == polygon)
        return;
    d->polygon = polygon;
    d->testResult->setPolygon(polygon);
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

void HTestWidget7000::setExportPath()
{
    Q_D(HTestWidget7000);
    d->exportPath = QFileDialog::getExistingDirectory(this, tr("导出目录"), ".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    d->textExport->setExportPath(d->exportPath);
}

void HTestWidget7000::editProduct()
{
    Q_D(HTestWidget7000);
    auto row = d->tableWidget->currentRow();
    auto data = d->testResult->at(row);
    if (data == nullptr)
        return;
    HProductEditDialog dlg(this);
    dlg.setData(data);
    if (dlg.exec() != QDialog::Accepted)
        return;
    d->testResult->setModified();
    d->tableWidget->refreshRow(row, data);
}

int HTestWidget7000::next(int index)
{
    Q_D(HTestWidget7000);
    index += 1;
    return index >= d->polygon.size() ? -1 : index;
}
