#include "HIVTestWidget_p.h"
#include "HIVTestSetWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/ITextStream.h"
#include "HeData/ITestData.h"
#include "HePlugin/HEntireTableWidget.h"
#include "HePlugin/HDynamicChartView.h"
#include <QtWidgets/QToolBar>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QHeaderView>
#include <QtCharts/QValueAxis>

HE_BEGIN_NAMESPACE

HIVTestWidgetPrivate::HIVTestWidgetPrivate()
{
    stream = HAppContext::getContextPointer<IDataFactory>("IDataFactory")->createTextStream("HTextStream");
    stream->setFileFilter("Excel files (*.xls)");
}

HIVTestWidget::HIVTestWidget(QWidget *parent) :
    HTestWidget(*new HIVTestWidgetPrivate, parent)
{
    init();
    setWindowTitle(tr("IV测试"));
}

HIVTestWidget::~HIVTestWidget() = default;

QString HIVTestWidget::typeName()
{
    return "HIVTestWidget";
}

void HIVTestWidget::createWidget()
{
    Q_D(HIVTestWidget);
    d->testSetWidget = new HIVTestSetWidget;
    d->tableWidget = new HEntireTableWidget;
    d->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("ID") << tr("电流(mA)") << tr("电压(V)"));
    d->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    d->tableWidget->verticalHeader()->setVisible(false);
    d->chartView = new HDynamicChartView;
    d->chartView->axisX()->setLabelFormat("%.2f mA");
    d->chartView->axisY()->setLabelFormat("%.2f V");
}

void HIVTestWidget::createMenu()
{

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
    toolBar2->setIconSize(QSize(40, 40));
    toolBar2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    d->toolBars << toolBar1 << toolBar2;
}

void HIVTestWidget::initWidget()
{
    Q_D(HIVTestWidget);
    auto layout = new QGridLayout(this);
    auto tabWidget = new QTabWidget;
    tabWidget->addTab(d->chartView, tr("测试图形"));
    tabWidget->addTab(d->tableWidget, tr("结果列表"));
    layout->addWidget(tabWidget, 1, 0, 1, 2);
    connect(d->testSetWidget, &ITestSetWidget::testStateChanged, this, &HIVTestWidget::handleStateChanged);
    connect(d->testSetWidget, &ITestSetWidget::resultChanged, this, &HIVTestWidget::handleResultChanged);
}

void HIVTestWidget::clearResult()
{
    Q_D(HIVTestWidget);
    d->data.clear();
    d->tableWidget->clearContents();
    d->tableWidget->setRowCount(0);
    d->chartView->clear();
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
    d->stream->setContent(text);
    d->stream->saveAsFile();
}

void HIVTestWidget::handleStateChanged(bool b)
{
    Q_D(HIVTestWidget);
    d->actionStart->setEnabled(!b);
    d->actionStop->setEnabled(b);
    d->actionExportExcel->setEnabled(!b);
    d->actionClear->setEnabled(!b);
    if (b)
        clearResult();
}

void HIVTestWidget::handleResultChanged()
{
    Q_D(HIVTestWidget);
    auto point = QPointF(d->testData->data("[输出电流]").toDouble(), d->testData->data("[实测电压]").toDouble());
    d->data.append(point);
    d->chartView->addPoint(point);
    d->tableWidget->insertRow(0, QStringList() << QString::number(d->data.count()) << d->testData->toString("[输出电流]") << d->testData->toString("[实测电压]"));
}

HE_END_NAMESPACE
