#include "HTestWidget1000RGB_p.h"
#include "HTestResult1000RGB.h"
#include "HTestSetWidget1000RGB.h"
#include "HeData/ITestData.h"
#include "HePlugin/HCie1931Widget.h"
#include "HePlugin/HCartesianWidget.h"
#include "HeGui/HResultTableWidget.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSplitter>

HTestWidget1000RGBPrivate::HTestWidget1000RGBPrivate()
{

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
    auto splitter3 = new QSplitter(Qt::Horizontal);
    d->energyWidget->setPolygonColor(0, Qt::red);
    d->energyWidget->setPolygonColor(1, Qt::green);
    d->energyWidget->setPolygonColor(2, Qt::blue);
    d->energyWidget->setPolygonColor(3, Qt::white);
    d->energyWidget->setPolygonColor(4, QColor(255, 85, 0));
    tabWidget1->addTab(d->energyWidget, tr("相对光谱功率分布"));
    //    tabWidget2->addTab(d->cieWidget, d->cieWidget->windowTitle());
    tabWidget3->addTab(d->tableWidgets[0], tr("R"));
    tabWidget3->addTab(d->tableWidgets[1], tr("G"));
    tabWidget3->addTab(d->tableWidgets[2], tr("B"));
    tabWidget3->addTab(d->tableWidgets[3], tr("W"));
    tabWidget3->addTab(d->tableWidgets[4], tr("综合"));
    splitter1->addWidget(tabWidget1);
    splitter1->addWidget(tabWidget2);
    splitter1->setHandleWidth(15);
    splitter1->setStretchFactor(0, 2);
    splitter1->setStretchFactor(1, 1);
    splitter2->addWidget(splitter1);
    splitter2->addWidget(tabWidget3);
    splitter2->setHandleWidth(15);
    splitter2->setStretchFactor(1, 1);
    splitter3->addWidget(splitter2);
    splitter3->addWidget(d->testSetWidget);
    splitter3->setHandleWidth(15);
    splitter3->setStretchFactor(0, 1);
    layout->addWidget(splitter3);
    resetSpec();
    resetGrade();
}

void HTestWidget1000RGB::clearResult()
{
    Q_D(HTestWidget1000RGB);
    d->testResult->clearResult();
    d->cieWidget->clearPoint();
    for (auto w : d->tableWidgets)
        w->clearResult();
}

void HTestWidget1000RGB::exportExcel()
{

}

void HTestWidget1000RGB::handleAction(HActionType)
{

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

