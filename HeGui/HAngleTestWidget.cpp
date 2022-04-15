#include "HAngleTestWidget_p.h"
#include "HAngleTestSetWidget.h"
#include "HAngleTestDetailWidget.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeData/ITestData.h"
#include "HeData/ITextExport.h"
#include "HeData/ITextExportTemplate.h"
#include "HeController/IModel.h"
#include "HePlugin/HDynamicChartView.h"
#include "HePlugin/HPolarChartView.h"
#include "HeSql/ISqlHandle.h"
#include "HeSql/HSql.h"
#include <QtCharts/QValueAxis>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMenu>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolBar>

HE_BEGIN_NAMESPACE

HAngleTestWidgetPrivate::HAngleTestWidgetPrivate()
{
    sqlHandle = HAppContext::getContextPointer<ISqlHandle>("IAngleSqlHandle");
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

void HAngleTestWidget::restoreState()
{
    Q_D(HAngleTestWidget);
    HTestWidget::restoreState();
    d->testData->setData("[光测试类型]", "[光强度]");
    d->model->addAction(ACT_SET_LUMINOUS_TYPE);
}

void HAngleTestWidget::createAction()
{
    Q_D(HAngleTestWidget);
    HTestWidget::createAction();
    d->actionExportDatabase = new QAction(tr("保存数据库(&D)"), this);
    d->actionExportDatabase->setIcon(QIcon(":/image/DbComit.png"));
    d->actionExportDatabase->setIconText(tr("保存数据库"));
    d->actionExportDatabase->setEnabled(false);
    connect(d->actionExportDatabase, &QAction::triggered, this, &HAngleTestWidget::exportDatabase);
}

void HAngleTestWidget::createWidget()
{
    Q_D(HAngleTestWidget);
    d->testSetWidget = new HAngleTestSetWidget;
    d->detailWidget = new HAngleTestDetailWidget;
    d->cartesianChartView = new HDynamicChartView;
    d->cartesianChartView->axisX()->setRange(0, 180);
    d->cartesianChartView->axisX()->setLabelFormat("%d");
    d->cartesianChartView->axisY()->setLabelFormat("%d");
    d->polarChartView = new HPolarChartView;
    d->polarChartView->axisAngular()->setLabelFormat("%d");
    d->polarChartView->axisRadial()->setLabelFormat("%d");
}

void HAngleTestWidget::createMenu()
{

}

void HAngleTestWidget::createToolBar()
{
    Q_D(HAngleTestWidget);
    auto toolBar1 = new QToolBar(tr("设置(&S)"));
    auto toolBar2 = new QToolBar(tr("操作(&O)"));
    toolBar1->addWidget(d->testSetWidget);
    toolBar2->addAction(d->actionStart);
    toolBar2->addAction(d->actionStop);
    toolBar2->addAction(d->actionExportExcel);
    toolBar2->addAction(d->actionExportDatabase);
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
    splitter1->setStretchFactor(0, 2);
    splitter1->setStretchFactor(1, 1);
    splitter2->addWidget(splitter1);
    splitter2->addWidget(d->detailWidget);
    splitter2->setHandleWidth(15);
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
}

void HAngleTestWidget::handleResultChanged(HActionType action, bool)
{
    Q_D(HAngleTestWidget);
    if (action == ACT_GET_LUMINOUS_DATA)
    {
        d->detailWidget->refreshData("[光强度]");
        return;
    }
    if (action == ACT_GET_ANGLE_DISTRIBUTION)
    {
        auto poly = d->testData->data("[光强角度分布]").value<QPolygonF>();
        d->detailWidget->refreshWidget();
        d->cartesianChartView->replace(poly);
        d->polarChartView->replace(poly);
    }
}

void HAngleTestWidget::exportDatabase()
{
    Q_D(HAngleTestWidget);
    if (d->sqlHandle == nullptr)
        return;
    auto record = HSql::toRecord(d->sqlHandle->field(), d->testData);
    d->sqlHandle->addRecord(record);
}

HE_END_NAMESPACE
