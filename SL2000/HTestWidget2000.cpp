#include "HTestWidget2000_p.h"
#include "HTestSetWidget2000.h"
#include "HDetailWidget2000.h"
#include "HeCore/HAppContext.h"
#include "HeController/ITestData.h"
#include "HeData/IConfigManage.h"
#include "HeData/IGradeCollection.h"
#include "HeGui/HSpecEnergyWidget.h"
#include "HeGui/HResultTableWidget.h"
#include "HePlugin/HCIE1931Widget.h"
#include <QtCore/QDateTime>
#include <QtWidgets/QAction>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtCore/QDebug>

HTestWidget2000Private::HTestWidget2000Private()
{
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
    displayOptionals = QStringList() << "[分级]" << "[测量日期]" << "[测量时间]"
                                     << "[光谱光通量]" << "[光功率]"
                                     << "[主波长]" << "[峰值波长]" << "[峰值带宽]"
                                     << "[色温]" << "[色纯度]"
                                     << "[色坐标]" << ("[色坐标uvp]") << "[Duv]"
                                     << "[红色比]" << "[绿色比]" << "[蓝色比]"
                                     << "[显色指数]" <<"[显色指数Rx]";
}

HTestWidget2000::HTestWidget2000(QWidget *parent) :
    HTestWidget(*new HTestWidget2000Private, parent)
{
    init();
    resetGrade();
}

HTestWidget2000::~HTestWidget2000()
{
    qDebug() << __func__;
}

void HTestWidget2000::initialize(QVariantMap /*param*/)
{

}

QString HTestWidget2000::typeName()
{
    return "HTestWidget2000";
}

bool HTestWidget2000::setTest(bool b)
{
    Q_D(HTestWidget2000);
    return d->testSetWidget->setTestState(b);
}

void HTestWidget2000::handleAction(HActionType action)
{
    Q_D(HTestWidget2000);
    if (action >= 0xF0000000)
    {
        setTest(false);
        clearResult();
        if (action == ACT_RESET_SPECTRUM)
            d->energyWidget->initCoordinate();
        if (action == ACT_RESET_GRADE)
            resetGrade();
        return;
    }
    if (action == ACT_GET_SPECTRUM)
    {
        postProcess();
        refreshWidget();
    }
    d->testSetWidget->handleAction(action);
}

void HTestWidget2000::createWidget()
{
    Q_D(HTestWidget2000);
    auto layout = new QGridLayout(this);
    auto tabWidget1 = new QTabWidget;
    auto tabWidget2 = new QTabWidget;
    auto tabWidget3 = new QTabWidget;
    auto splitter1 = new QSplitter(Qt::Horizontal);
    auto splitter2 = new QSplitter(Qt::Vertical);
    d->testSetWidget = new HTestSetWidget2000;
    d->energyWidget = new HSpecEnergyWidget;
    d->cieWidget = new HCIE1931Widget;
    d->detailWidget = new HDetailWidget2000;
    d->resultWidget = new HResultTableWidget;
    d->resultWidget->setOptionals(d->displayOptionals);
    tabWidget1->addTab(d->energyWidget, d->energyWidget->windowTitle());
    tabWidget2->addTab(d->cieWidget, d->cieWidget->windowTitle());
    tabWidget3->addTab(d->detailWidget, tr("当次结果"));
    tabWidget3->addTab(d->resultWidget, tr("结果列表"));
    splitter1->addWidget(tabWidget1);
    splitter1->addWidget(tabWidget2);
    splitter1->setHandleWidth(15);
    splitter1->setStretchFactor(0, 1);
    splitter2->addWidget(splitter1);
    splitter2->addWidget(tabWidget3);
    splitter2->setHandleWidth(15);
    splitter2->setStretchFactor(1, 1);
    layout->addWidget(splitter2);
    connect(d->testSetWidget, &ITestSetWidget::testStateChanged, this, &HTestWidget2000::handleTestStateChanged);
}

void HTestWidget2000::createAction()
{
    Q_D(HTestWidget2000);
    HTestWidget::createAction();
    d->actionClear = new QAction(tr("清除结果(&R)..."), this);
    d->actionClear->setIcon(QIcon(":/image/Clear.png"));
    d->actionClear->setIconText(tr("清除结果"));
    connect(d->actionClear, &QAction::triggered, this, &HTestWidget2000::clearResult);
}

void HTestWidget2000::createMenu()
{
}

void HTestWidget2000::createToolBar()
{
    Q_D(HTestWidget2000);
    auto toolBar1 = new QToolBar(tr("设置(&S)"));
    auto toolBar2 = new QToolBar(tr("操作(&O)"));
    toolBar1->addWidget(d->testSetWidget);
    toolBar2->addAction(d->actionStart);
    toolBar2->addAction(d->actionStop);
    toolBar2->addAction(d->actionClear);
    toolBar2->addAction(d->actionExportExcel);
    toolBar2->addAction(d->actionExportDatabase);
    d->toolBars << toolBar1 << toolBar2;
}

void HTestWidget2000::initMenu()
{
}

void HTestWidget2000::handleTestStateChanged(bool b)
{
    Q_D(HTestWidget2000);
    d->actionStart->setEnabled(!b);
    d->actionStop->setEnabled(b);
    d->actionExportExcel->setEnabled(!b);
    d->actionExportDatabase->setEnabled(!b);
    d->actionClear->setEnabled(!b);
}

void HTestWidget2000::resetGrade()
{
    Q_D(HTestWidget2000);
    auto v = d->configManage->gradeCollection()->levels("[色坐标]");
    auto p = v.value<QList<QPolygonF>>();
    d->cieWidget->setGrade(p);
}

void HTestWidget2000::refreshWidget()
{
    Q_D(HTestWidget2000);
    d->energyWidget->refreshWidget();
    d->detailWidget->refreshWidget();
    d->cieWidget->addPoint(d->testData->data("[色坐标]").toPointF());
    d->resultWidget->refreshResult(0, d->testSetWidget->testMode() == 0);
}

void HTestWidget2000::clearResult()
{
    Q_D(HTestWidget2000);
    d->cieWidget->clearPoint();
    d->resultWidget->clearResult();
}

void HTestWidget2000::postProcess()
{
    Q_D(HTestWidget2000);
    QString text;
    auto r = d->testData->select(d->displayOptionals);
    auto l = d->configManage->gradeCollection()->calcLevel(r, text);
    d->testData->setData("[分级]", l);
    d->testData->setData("[分级别名]", text);
    d->testData->setData("[测量日期时间]", QDateTime::currentDateTime());
}
