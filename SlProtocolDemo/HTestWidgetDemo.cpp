#include "HTestWidgetDemo_p.h"
#include "HTestSetWidgetDemo.h"
#include "HeData/ITestSpec.h"
#include "HeData/ISpecCalibrate.h"
#include "HeData/HSpecFitting.h"
#include "HeData/HSpecPelsWave.h"
#include "HeController/IModel.h"
#include "HeGui/HSpecSampleChartView.h"
#include "HeGui/HSpecFittingChartView.h"
#include "HeGui/HSpecEnergyWidget.h"
#include "HeGui/HSpecPelsWaveWidget.h"
#include "HeGui/HSpecFittingLinearWidget.h"
#include "HeGui/HSpecFittingPolynomWidget.h"
#include "HeGui/HSpecDetailWidget.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSplitter>
#include <QtCore/QDebug>

HTestWidgetDemo::HTestWidgetDemo(QWidget *parent) :
    HTestWidget2(*new HTestWidgetDemoPrivate, parent)
{
    init();
}

HTestWidgetDemo::~HTestWidgetDemo()
{
    qDebug() << __func__;
}

void HTestWidgetDemo::initialize(QVariantMap /*param*/)
{

}

QString HTestWidgetDemo::typeName()
{
    return "HTestWidgetDemo";
}

void HTestWidgetDemo::setSpecCalibrate(ISpecCalibrate *p)
{
    Q_D(HTestWidgetDemo);

    if (d->specCalibrate != nullptr)
        d->tabWidget->removeTab(d->tabWidget->indexOf(d->fittingWidget));

    auto f = dynamic_cast<HSpecFitting *>(p->item(ISpecCalibrate::Fitting));
    auto w = dynamic_cast<HSpecPelsWave *>(p->item(ISpecCalibrate::PelsWave));

    d->specCalibrate = p;
    if (f->typeName() == "HSpecFittingPolynom")
        d->fittingWidget = new HSpecFittingPolynomWidget;
    else
        d->fittingWidget = new HSpecFittingLinearWidget;
    d->fittingWidget->setData(f);
    d->pelsWaveWidget->setData(w);
    d->tabWidget->addTab(d->fittingWidget, d->fittingWidget->windowTitle());
    refreshCcdView();
}

bool HTestWidgetDemo::setTest(bool b)
{
    Q_D(HTestWidgetDemo);
    return d->testSetWidget->setTestState(b);
}

void HTestWidgetDemo::handleAction(HActionType action)
{
    Q_D(HTestWidgetDemo);
    if (action == ACT_GET_SPECTRUM || action == ACT_GET_SPECTRUM_ENERGY)
        refreshSpecWidget();
    d->testSetWidget->handleAction(action);
}

void HTestWidgetDemo::createAction()
{
    Q_D(HTestWidgetDemo);
    HTestWidget2::createAction();
    d->actionImport = new QAction(tr("导入标准(&I)"), this);
    d->actionImport->setIcon(QIcon(":/image/Import.png"));
    d->actionImport->setIconText(tr("导入标准"));
    connect(d->actionImport, &QAction::triggered, this, [=] { d->model->addAction(ACT_SET_DATA); });
}

void HTestWidgetDemo::createWidget()
{
    Q_D(HTestWidgetDemo);
    d->sampleView = new HSpecSampleChartView;
    d->ccdView = new HSpecFittingChartView;
    d->energyWidget = new HSpecEnergyWidget;
    d->pelsWaveWidget = new HSpecPelsWaveWidget;
    d->testSetWidget = new HTestSetWidgetDemo;
    d->detailWidget = new HSpecDetailWidget;
    auto layout = new QGridLayout(this);
    auto splitter = new QSplitter(Qt::Horizontal);
    auto tabWidget1 = new QTabWidget;
    d->tabWidget = new QTabWidget;
    tabWidget1->addTab(d->sampleView, d->sampleView->windowTitle());
    tabWidget1->addTab(d->energyWidget, d->energyWidget->windowTitle());
    tabWidget1->addTab(d->ccdView, d->ccdView->windowTitle());
    d->tabWidget->addTab(d->pelsWaveWidget, d->pelsWaveWidget->windowTitle());
    d->tabWidget->addTab(d->detailWidget, d->detailWidget->windowTitle());
    splitter->addWidget(tabWidget1);
    splitter->addWidget(d->tabWidget);
    splitter->setHandleWidth(15);
    splitter->setStretchFactor(0, 1);
    layout->addWidget(splitter);
    connect(d->testSetWidget, &ITestSetWidget::stateChanged, this, &HTestWidgetDemo::handleStateChanged);
}

void HTestWidgetDemo::createMenu()
{

}

void HTestWidgetDemo::createToolBar()
{
    Q_D(HTestWidgetDemo);
    auto toolBar1 = new QToolBar(tr("设置(&S)"));
    auto toolBar2 = new QToolBar(tr("操作(&O)"));
    toolBar1->addWidget(d->testSetWidget);
    toolBar2->addAction(d->actionStart);
    toolBar2->addAction(d->actionStop);
    toolBar2->addAction(d->actionImport);
    d->toolBars << toolBar1 << toolBar2;
}

void HTestWidgetDemo::handleStateChanged(bool b)
{
    Q_D(HTestWidgetDemo);
    d->actionStart->setEnabled(!b);
    d->actionStop->setEnabled(b);
}

void HTestWidgetDemo::refreshCcdView()
{
    Q_D(HTestWidgetDemo);
    d->ccdView->addLineSeries(1, d->fittingWidget->fittingCurve());
    d->ccdView->addScatterSeries(1, d->fittingWidget->fittingPoints());
}

void HTestWidgetDemo::refreshSpecWidget()
{
    Q_D(HTestWidgetDemo);
    d->sampleView->refreshWidget();
    d->energyWidget->refreshWidget();
    d->detailWidget->refreshWidget();
}
