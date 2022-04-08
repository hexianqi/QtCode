#include "HAngleTestWidget_p.h"
#include "HAngleTestSetWidget.h"
#include "HAngleTestDetailWidget.h"
#include "HeData/ITestData.h"
#include "HeController/IModel.h"
#include "HePlugin/HDynamicChartView.h"
#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>

HE_BEGIN_NAMESPACE

HAngleTestWidget::HAngleTestWidget(QWidget *parent) :
    HTestWidget(*new HAngleTestWidgetPrivate, parent)
{
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
    HTestWidget::createWidget();
    d->testSetWidget = new HAngleTestSetWidget;
    d->detailWidget = new HAngleTestDetailWidget;
    d->chartView = new HDynamicChartView;
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
 //   toolBar2->addAction(d->actionClear);
    toolBar2->addAction(d->actionExportExcel);
    toolBar2->addAction(d->actionExportDatabase);
    toolBar2->setIconSize(QSize(40, 40));
    toolBar2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    d->toolBars << toolBar1 << toolBar2;
}

HE_END_NAMESPACE
