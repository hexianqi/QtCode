#include "HTestWidget1000RGB_p.h"
#include "HTestResult1000RGB.h"
#include "HTestSetWidget1000RGB.h"
#include "HeCore/HCore.h"
#include "HeData/ITestData.h"
#include "HePlugin/HCie1931Widget.h"
#include "HePlugin/HCartesianWidget.h"
#include "HeGui/HResultTableWidget.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolBar>

HTestWidget1000RGBPrivate::HTestWidget1000RGBPrivate()
{
    auto list = HCore::membership("|光谱信息4|");
    displays.insert(0, QStringList() << "[实测电压-R]" << "[实测电流-R]" << "[反向漏流-R]" << list);
    displays.insert(1, QStringList() << "[实测电压-G]" << "[实测电流-G]" << "[反向漏流-G]" << list);
    displays.insert(2, QStringList() << "[实测电压-B]" << "[实测电流-B]" << "[反向漏流-B]" << list);
    displays.insert(3, QStringList() << "[实测电压-W]" << "[实测电流-W]" << "[反向漏流-W]" << list);
    displays.insert(4, QStringList() << "[实测电压-R]" << "[实测电流-R]" << "[反向漏流-R]"
                                     << "[实测电压-G]" << "[实测电流-G]" << "[反向漏流-G]"
                                     << "[实测电压-B]" << "[实测电流-B]" << "[反向漏流-B]"
                                     << "[实测电压-W]" << "[实测电流-W]" << "[反向漏流-W]" << list);
}

HTestWidget1000RGB::HTestWidget1000RGB(QWidget *parent) :
    HTestWidget(*new HTestWidget1000RGBPrivate, parent)
{
    init();
}

HTestWidget1000RGB::~HTestWidget1000RGB()
{

}

QString HTestWidget1000RGB::typeName()
{
    return "HTestWidget1000RGB";
}

void HTestWidget1000RGB::init()
{
    Q_D(HTestWidget1000RGB);
    HTestWidget::init();
    d->testResult = new HTestResult1000RGB(this);
}

void HTestWidget1000RGB::createWidget()
{
    Q_D(HTestWidget1000RGB);
    d->testSetWidget = new HTestSetWidget1000RGB;
    d->cieWidget = new HCie1931Widget;
    d->energyWidget = new HCartesianWidget;
    d->tableWidgets.insert(0, new HResultTableWidget);
    d->tableWidgets.insert(1, new HResultTableWidget);
    d->tableWidgets.insert(2, new HResultTableWidget);
    d->tableWidgets.insert(3, new HResultTableWidget);
    d->tableWidgets.insert(4, new HResultTableWidget);
}

void HTestWidget1000RGB::createMenu()
{

}

void HTestWidget1000RGB::createToolBar()
{
    Q_D(HTestWidget1000RGB);
    auto toolBar = new QToolBar(tr("操作(&O)"));
    toolBar->addAction(d->actionStart);
    toolBar->addAction(d->actionStop);
    toolBar->addAction(d->actionClear);
    d->toolBars << toolBar;
}

void HTestWidget1000RGB::initWidget()
{
    Q_D(HTestWidget1000RGB);
    auto layout = new QGridLayout(this);
    auto tabWidget1 = new QTabWidget;
    auto tabWidget2 = new QTabWidget;
    auto tabWidget3 = new QTabWidget;
    auto splitter1 = new QSplitter(Qt::Horizontal);
    auto splitter2 = new QSplitter(Qt::Vertical);
    d->energyWidget->setPolygonColor(0, Qt::red);
    d->energyWidget->setPolygonColor(1, Qt::green);
    d->energyWidget->setPolygonColor(2, Qt::blue);
    d->energyWidget->setPolygonColor(3, Qt::white);
    d->energyWidget->setPolygonColor(4, QColor(255, 85, 0));
    d->tableWidgets[0]->setDisplay(d->displays[0]);
    d->tableWidgets[1]->setDisplay(d->displays[1]);
    d->tableWidgets[2]->setDisplay(d->displays[2]);
    d->tableWidgets[3]->setDisplay(d->displays[3]);
    d->tableWidgets[4]->setDisplay(d->displays[4]);
//    tabWidget1->addTab(d->cieWidget, d->cieWidget->windowTitle());
    tabWidget2->addTab(d->energyWidget, tr("相对光谱功率分布"));
    tabWidget3->addTab(d->tableWidgets[0], tr("R"));
    tabWidget3->addTab(d->tableWidgets[1], tr("G"));
    tabWidget3->addTab(d->tableWidgets[2], tr("B"));
    tabWidget3->addTab(d->tableWidgets[3], tr("W"));
    tabWidget3->addTab(d->tableWidgets[4], tr("综合"));
    splitter1->addWidget(tabWidget1);
    splitter1->addWidget(tabWidget2);
    splitter1->addWidget(d->testSetWidget);
    splitter1->setHandleWidth(15);
    splitter1->setStretchFactor(0, 1);
    splitter1->setStretchFactor(1, 1);
    splitter2->addWidget(splitter1);
    splitter2->addWidget(tabWidget3);
    splitter2->setHandleWidth(15);
    splitter2->setStretchFactor(1, 1);
    layout->addWidget(splitter2);
//    connect(d->testSetWidget, &ITestSetWidget::testStateChanged, this, &HTestWidget1000RGB::handleStateChanged);
//    connect(d->testSetWidget, &ITestSetWidget::resultChanged, this, &HTestWidget1000RGB::handleResultChanged);
    connect(d->testSetWidget, SIGNAL(testStateChanged(bool)), this, SLOT(handleStateChanged(bool)));
    connect(d->testSetWidget, SIGNAL(resultChanged(HActionType, bool)), this, SLOT(handleResultChanged(HActionType, bool)));
    resetSpec();
    resetGrade();
}

void HTestWidget1000RGB::clearResult()
{
    Q_D(HTestWidget1000RGB);
    d->testResult->clear();
    d->energyWidget->clearPolygon();
    d->cieWidget->clearPoint();
    for (auto w : d->tableWidgets)
        w->clearResult();
}

void HTestWidget1000RGB::exportExcel()
{

}

void HTestWidget1000RGB::handleAction(HActionType action)
{
 //   Q_D(HTestWidget1000RGB);
    if (action >= 0xF0000000)
    {
        setTest(false);
        clearResult();
        if (action == ACT_RESET_SPECTRUM)
            resetSpec();
//        if (action == ACT_RESET_CHROMATISM)
//            d->chromatismWidget->initMenuShow();
        if (action == ACT_RESET_GRADE)
            resetGrade();
        return;
    }
    HTestWidget::handleAction(action);
}

void HTestWidget1000RGB::handleStateChanged(bool b)
{
    Q_D(HTestWidget1000RGB);
    d->actionStart->setEnabled(!b);
    d->actionStop->setEnabled(b);
    d->actionClear->setEnabled(!b);
    if (b)
        d->energyWidget->clearPolygon();
}

void HTestWidget1000RGB::handleResultChanged(HActionType, bool append)
{
    Q_D(HTestWidget1000RGB);
    refreshWidget(append);
    d->testResult->update(append);
}

void HTestWidget1000RGB::resetSpec()
{
    Q_D(HTestWidget1000RGB);
    auto waveRange = d->testData->data("[光谱波长范围]").toPointF();
    d->energyWidget->setCoordinate(QRectF(waveRange.x(), 0, waveRange.y() - waveRange.x(), 100), 10, 5);
}

void HTestWidget1000RGB::resetGrade()
{

}

void HTestWidget1000RGB::refreshWidget(bool append)
{
    Q_D(HTestWidget1000RGB);
    auto id = d_ptr->testData->data("[TypeId]").toInt();
    auto point = d->testData->data("[色坐标]").toPointF();
    d->energyWidget->addPolygon(id, d_ptr->testData->data("[光谱能量曲线]").value<QPolygonF>());
    d->tableWidgets[id]->refreshLast(append);
    if (append)
        d->cieWidget->addPoint(point);
    else
        d->cieWidget->setPointFocus(point);
}

