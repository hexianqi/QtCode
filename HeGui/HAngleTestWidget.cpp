#include "HAngleTestWidget_p.h"
#include "HAngleTestSetWidget.h"
#include "HAngleTestDetailWidget.h"
#include "HAngleChartView.h"
#include "HAction.h"
#include "IGuiFactory.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeData/IConfigManage.h"
#include "HeData/ITestData.h"
#include "HeData/IPrint.h"
#include "HeData/IPrintTemplate.h"
#include "HeData/ITextExport.h"
#include "HeData/ITextExportTemplate.h"
#include "HeController/IModel.h"
#include "HeController/IMementoCollection.h"
#include "HePlugin/HDynamicChartView.h"
#include "HeSql/ISqlHandle.h"
#include "HeSql/HSql.h"
#include <QtCore/QTimer>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMenu>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolBar>
#include <QtCharts/QValueAxis>
#include <QtCharts/QScatterSeries>

HE_BEGIN_NAMESPACE

HAngleTestWidgetPrivate::HAngleTestWidgetPrivate()
{
    auto mementoCollection = HAppContext::getContextPointer<IMementoCollection>("IMementoCollection");
    memento = mementoCollection->value("Angle");
    guiFactory = HAppContext::getContextPointer<IGuiFactory>("IGuiFactory");
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
    sqlHandle = HAppContext::getContextPointer<ISqlHandle>("IAngleSqlHandle");
    print = HAppContext::getContextPointer<IPrint>("IPrint");
    printTemplate = HAppContext::getContextPointer<IPrintTemplate>("IAnglePrintTemplate");
    textExport = HAppContext::getContextPointer<ITextExport>("ITextExport");
    textExportTemplate = HAppContext::getContextPointer<ITextExportTemplate>("IAngleTextExportTemplate");
}

HAngleTestWidget::HAngleTestWidget(QWidget *parent) :
    HTestWidget(*new HAngleTestWidgetPrivate, parent)
{
    init();
    setWindowTitle(tr("光强角度分布测试"));
}

HAngleTestWidget::~HAngleTestWidget() = default;

QString HAngleTestWidget::typeName()
{
    return "HAngleTestWidget";
}

void HAngleTestWidget::init()
{
    Q_D(HAngleTestWidget);
    HTestWidget::init();
    d->timer = new QTimer(this);
    d->timer->setInterval(1000);
    connect(d->timer, &QTimer::timeout, this, &HAngleTestWidget::handleTimer);
}

void HAngleTestWidget::saveState()
{
    Q_D(HAngleTestWidget);
    HTestWidget::saveState();
    d->timer->stop();
    d->testData->setData("[电源模式]", 0);
    d->model->addAction(ACT_SET_SOURCE_MODE, 200);
}

void HAngleTestWidget::restoreState()
{
    Q_D(HAngleTestWidget);
    HTestWidget::restoreState();
    d->testData->setData("[光测试类型]", "[光强度]");
    d->model->addAction(ACT_SET_LUMINOUS_TYPE);
    d->testData->setData("[电源模式]", 1);
    d->model->addAction(ACT_SET_SOURCE_MODE, 200);
    d->testSetWidget->handleOperation("<复位电机>");
    d->timer->start();
}

void HAngleTestWidget::handleAction(HActionType action)
{
    Q_D(HAngleTestWidget);
    if (action == ACT_QUERY_MOTOR_STATE)
    {
        auto state = d->testData->data("[电机状态]").toInt();
        d->actionMotorLocation->setEnabled(state == 1);
        d->actionMotorReset->setEnabled(state == 1);
    }
    HTestWidget::handleAction(action);
}

void HAngleTestWidget::createAction()
{
    Q_D(HAngleTestWidget);
    HTestWidget::createAction();
    d->actionMotorLocation = new QAction(tr("转动电机(&L)"), this);
    d->actionMotorLocation->setIcon(QIcon(":/image/Motor.png"));
    d->actionMotorLocation->setIconText(tr("转动电机"));
    d->actionMotorReset = new QAction(tr("复位电机(&R)"), this);
    d->actionMotorReset->setIcon(QIcon(":/image/Reset.png"));
    d->actionMotorReset->setIconText(tr("复位电机"));
    d->actionExportDatabase = new QAction(tr("保存数据库(&D)"), this);
    d->actionExportDatabase->setIcon(QIcon(":/image/DbComit.png"));
    d->actionExportDatabase->setIconText(tr("保存数据库"));
    d->actionExportDatabase->setEnabled(false);
    d->actionPrintPreview = new QAction(tr("打印预览(&V)"), this);
    d->actionPrintPreview->setIcon(QIcon(":/image/PrintPreview.png"));
    d->actionPrintPreview->setIconText(tr("打印预览"));
    d->actionPrintPreview->setEnabled(false);
    connect(d->actionMotorLocation, &QAction::triggered, this, [=] { d->testSetWidget->handleOperation("<转动电机>"); });
    connect(d->actionMotorReset, &QAction::triggered, this, [=] { d->testSetWidget->handleOperation("<复位电机>"); });
    connect(d->actionExportDatabase, &QAction::triggered, this, &HAngleTestWidget::exportDatabase);
    connect(d->actionPrintPreview, &QAction::triggered, this, &HAngleTestWidget::printPreview);
}

void HAngleTestWidget::createWidget()
{
    Q_D(HAngleTestWidget);
    d->testSetWidget = new HAngleTestSetWidget;
    d->detailWidget = new HAngleTestDetailWidget;
    d->cartesianChartView = new HDynamicChartView;
    d->cartesianChartView->axisX()->setRange(-90, 90);
    d->cartesianChartView->axisX()->setLabelFormat("%d");
    d->cartesianChartView->axisY()->setRange(0, 10);
    d->cartesianChartView->axisY()->setLabelFormat("%d");
    d->cartesianChartView->scatterSeries()->setVisible(false);
    d->cartesianChartView->chart()->legend()->setVisible(false);
    d->polarChartView = new HAngleChartView;
    d->polarChartView->axisAngular()->setRange(-180, 180);
    d->polarChartView->axisAngular()->setLabelFormat("%d");
    d->polarChartView->axisRadial()->setRange(0, 10);
    d->polarChartView->axisRadial()->setLabelFormat("%d");
}

void HAngleTestWidget::createMenu()
{
    Q_D(HAngleTestWidget);
    QVariantMap param[2];
    param[0].insert("key", "Angle");
    param[0].insert("optional", "AngleQualityOptional");
    param[1].insert("sqlBrowser", "IAngleSqlBrowser");
    auto quality = new QMenu(tr("品质(&Q)"));
    auto database = new QMenu(tr("数据库(&D)"));
    quality->addAction(d->guiFactory->createAction(tr("光强角品质数据配置(&E)..."), "HQualityEditHandler", param[0]));
    quality->addAction(d->guiFactory->createAction(tr("光强角品质数据选择(&S)..."), "HQualitySelectHandler", param[0]));
    database->addAction(d->guiFactory->createAction(tr("光强角数据库浏览(&B)..."), "HSqlBrowserHandler", param[1]));
    d->menus << quality << database;
}

void HAngleTestWidget::createToolBar()
{
    Q_D(HAngleTestWidget);
    auto toolBar1 = new QToolBar(tr("设置(&S)"));
    auto toolBar2 = new QToolBar(tr("操作(&O)"));
    toolBar1->addWidget(d->testSetWidget);
    toolBar2->addAction(d->actionStart);
    toolBar2->addAction(d->actionStop);
    toolBar2->addAction(d->actionMotorReset);
    toolBar2->addAction(d->actionMotorLocation);
    toolBar2->addAction(d->actionExportExcel);
    toolBar2->addAction(d->actionExportDatabase);
    toolBar2->addAction(d->actionPrintPreview);
    toolBar2->setIconSize(QSize(40, 40));
    toolBar2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    d->toolBars << toolBar1 << toolBar2;
}

void HAngleTestWidget::initWidget()
{
    Q_D(HAngleTestWidget);
    auto layout = new QGridLayout(this);
    auto splitter1 = new QSplitter(Qt::Horizontal);
    auto splitter2 = new QSplitter(Qt::Vertical);
    splitter1->addWidget(d->cartesianChartView);
    splitter1->addWidget(d->polarChartView);
    splitter1->setHandleWidth(15);
    splitter1->setStretchFactor(0, 1);
    splitter1->setStretchFactor(1, 1);
    splitter2->addWidget(splitter1);
    splitter2->addWidget(d->detailWidget);
    splitter2->setHandleWidth(15);
    splitter2->setStretchFactor(0, 2);
    splitter2->setStretchFactor(1, 1);
    layout->addWidget(splitter2);
    connect(d->testSetWidget, &ITestSetWidget::testStateChanged, this, &HAngleTestWidget::handleStateChanged);
    connect(d->testSetWidget, &ITestSetWidget::resultChanged, this, &HAngleTestWidget::handleResultChanged);
}

void HAngleTestWidget::clearResult()
{

}

void HAngleTestWidget::exportExcel()
{
    Q_D(HAngleTestWidget);
    auto type = HCore::membership("|光强角度信息|");
    d->textExportTemplate->setDataType(type);
    d->textExportTemplate->setData(d->testData->select(type));
    d->textExport->setTextTemplate(d->textExportTemplate);
    d->textExport->saveAs();
}

void HAngleTestWidget::handleStateChanged(bool b)
{
    Q_D(HAngleTestWidget);
    d->actionStart->setEnabled(!b);
    d->actionStop->setEnabled(b);
    d->actionClear->setEnabled(!b);
    d->actionExportExcel->setEnabled(!b);
    d->actionExportDatabase->setEnabled(!b);
    d->actionPrintPreview->setEnabled(!b);
    d->actionMotorLocation->setEnabled(!b);
    d->actionMotorReset->setEnabled(!b);
    if (b)
        d->timer->stop();
    else
        d->timer->start();
}

void HAngleTestWidget::handleResultChanged(HActionType action, bool)
{
    Q_D(HAngleTestWidget);
    if (action == ACT_GET_MEASURED_VOLTAGE)
    {
        d->detailWidget->refreshData("[实测电压]");
        return;
    }
    if (action == ACT_GET_LUMINOUS_DATA)
    {
        d->detailWidget->refreshData("[光强度]");
        return;
    }
    if (action == ACT_GET_ANGLE_DISTRIBUTION)
    {
        auto poly = d->testData->data("[光强角度分布]").value<QPolygonF>();
        d->configManage->processQuality(d->testData, HCore::membership("|光强角度信息2|"), "Angle");
        d->detailWidget->refreshWidget();
        d->cartesianChartView->replace(poly);
        d->polarChartView->replace(poly);
        d->polarChartView->setAngleFifth(d->testData->data("[左1/5光强度角]").toDouble(), d->testData->data("[右1/5光强度角]").toDouble());
        d->polarChartView->setAngleHalf(d->testData->data("[左半光强度角]").toDouble(), d->testData->data("[右半光强度角]").toDouble());
        return;
    }
}

void HAngleTestWidget::handleTimer()
{
    Q_D(HAngleTestWidget);
    d->model->addAction(ACT_GET_MEASURED_VOLTAGE);
    d->model->addAction(ACT_GET_LUMINOUS_DATA);
}

void HAngleTestWidget::exportDatabase()
{
    Q_D(HAngleTestWidget);
    if (d->sqlHandle == nullptr)
        return;
    auto record = HSql::toRecord(d->sqlHandle->field(), d->testData);
    d->sqlHandle->addRecord(record);
}

void HAngleTestWidget::printPreview()
{
    Q_D(HAngleTestWidget);
    d->printTemplate->setData(d->testData->select(d->printTemplate->dataType()));
    d->print->setPrintTemplate(d->printTemplate);
    d->print->printPreview();
}

HE_END_NAMESPACE
