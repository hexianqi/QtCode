#include "HIVTestWidget_p.h"
#include "HIVTestSetWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/IExcelStream.h"
#include "HePlugin/HEntireTableWidget.h"
#include "HePlugin/HDynamicChartView.h"
#include "HeData/ITestData.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTabWidget>
#include <QtCharts/QValueAxis>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HIVTestWidgetPrivate::HIVTestWidgetPrivate()
{
    excelStream = HAppContext::getContextPointer<IDataFactory>("IDataFactory")->createExcelStream("HExcelStream");
    testSetWidget = new HIVTestSetWidget;
    tableWidget = new HEntireTableWidget;
    chartView = new HDynamicChartView;
}

HIVTestWidget::HIVTestWidget(QWidget *parent) :
    HAbstractTestWidget(*new HIVTestWidgetPrivate, parent)
{
    init();
    start();
}

HIVTestWidget::~HIVTestWidget()
{
    qDebug() << __func__;
    setTest(false);
    stop();
}

void HIVTestWidget::initialize(QVariantMap /*param*/)
{

}

QString HIVTestWidget::typeName()
{
    return "HIVTestWidget";
}

bool HIVTestWidget::setTest(bool b)
{
    Q_D(HIVTestWidget);
    return d->testSetWidget->setTestState(b);
}

void HIVTestWidget::handleAction(HActionType action)
{
    Q_D(HIVTestWidget);
    if (action == ACT_GET_MEASURED_VOLTAGE)
    {
        auto point = QPointF(d->testData->data("[输出电流]").toDouble(), d->testData->data("[实测电压]").toDouble());
        d->data.append(point);
        d->chartView->addPoint(point);
        d->tableWidget->insertRow(0, QStringList() << QString::number(d->data.count()) << d->testData->toString("[输出电流]") << d->testData->toString("[实测电压]"));
    }
    d->testSetWidget->handleAction(action);
}

void HIVTestWidget::exportExcel()
{
    Q_D(HIVTestWidget);
    if (d->data.isEmpty())
        return;
    QString text;
    text += tr("ID\t电流(mA)\t电压(V)") + "\n";
    for (int i = 0; i < d->data.count(); i++)
        text += QString("%1\t%2\t%3\n").arg(i+1).arg(d->data[i].x()).arg(d->data[i].y());
    d->excelStream->setWriteContent(text);
    d->excelStream->saveAsFile();
}

void HIVTestWidget::clearResult()
{
    Q_D(HIVTestWidget);
    d->data.clear();
    d->tableWidget->clearContents();
    d->tableWidget->setRowCount(0);
    d->chartView->clear();
}

void HIVTestWidget::handleTestStateChanged(bool b)
{
    Q_D(HIVTestWidget);
    d->actionStart->setEnabled(!b);
    d->actionStop->setEnabled(b);
    d->actionExportExcel->setEnabled(!b);
    d->actionClear->setEnabled(!b);
    if (b)
        clearResult();
}

void HIVTestWidget::init()
{
    createAction();
    createToolBar();
    createWidget();
    setWindowTitle(tr("IV测试"));
}

void HIVTestWidget::createAction()
{
    Q_D(HIVTestWidget);
    d->actionStart = new QAction(tr("测量(&S)"), this);
    d->actionStart->setIcon(QIcon(":/image/Start02.png"));
    d->actionStart->setIconText(tr("测量"));
    d->actionStart->setShortcut(Qt::Key_F3);
    d->actionStop = new QAction(tr("停止(&T)"), this);
    d->actionStop->setIcon(QIcon(":/image/Stop02.png"));
    d->actionStop->setIconText(tr("停止"));
    d->actionStop->setShortcut(Qt::Key_F4);
    d->actionStop->setEnabled(false);
    d->actionExportExcel = new QAction(tr("导出结果(&E)"), this);
    d->actionExportExcel->setIcon(QIcon(":/image/Excel.png"));
    d->actionExportExcel->setIconText(tr("导出结果"));
    d->actionClear = new QAction(tr("清除结果(&R)..."), this);
    d->actionClear->setIcon(QIcon(":/image/Clear.png"));
    d->actionClear->setIconText(tr("清除结果"));
    connect(d->actionStart, &QAction::triggered, this, [=] { setTest(true); });
    connect(d->actionStop, &QAction::triggered, this, [=] { setTest(false); });
    connect(d->actionExportExcel, &QAction::triggered, this, &HIVTestWidget::exportExcel);
    connect(d->actionClear, &QAction::triggered, this, &HIVTestWidget::clearResult);
}

void HIVTestWidget::createToolBar()
{
    Q_D(HIVTestWidget);
    auto toolBar1 = new QToolBar(tr("设置(&S)"));
    auto toolBar2 = new QToolBar(tr("操作(&O)"));
    toolBar1->addWidget(d->testSetWidget);
    toolBar2->addAction(d->actionStart);
    toolBar2->addAction(d->actionStop);
    toolBar2->addAction(d->actionClear);
    toolBar2->addAction(d->actionExportExcel);
    toolBar2->setIconSize(QSize(40,40));
    toolBar2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    d->toolBars << toolBar1 << toolBar2;
}

void HIVTestWidget::createWidget()
{
    Q_D(HIVTestWidget);
    auto layout = new QGridLayout(this);
    auto tabWidget = new QTabWidget;
    d->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("ID") << tr("电流(mA)") << tr("电压(V)"));
    d->chartView->axisX()->setLabelFormat("%.2f mA");
    d->chartView->axisY()->setLabelFormat("%.2f V");
    tabWidget->addTab(d->chartView, tr("测试图形"));
    tabWidget->addTab(d->tableWidget, tr("结果列表"));
    layout->addWidget(d->toolBars[0], 0, 0);
    layout->addWidget(d->toolBars[1], 0, 1);
    layout->addWidget(tabWidget, 1, 0, 1, 2);
    connect(d->testSetWidget, &ITestSetWidget::testStateChanged, this, &HIVTestWidget::handleTestStateChanged);
}

HE_GUI_END_NAMESPACE
