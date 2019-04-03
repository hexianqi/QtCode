#include "HTestWidgetSpec_p.h"
#include "ui_HTestWidgetSpec.h"
#include "HDetailWidgetSpec.h"
#include "HTestSetWidgetSpec.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include "HeController/ITestSpec.h"
#include "HeData/IConfigManage.h"
#include "HeData/ISpecCalibrate.h"
#include "HeData/HSpecSetting.h"
#include "HeData/HSpecFitting.h"
#include "HeData/HSpecStdCurve.h"
#include "HeData/HSpecPelsWave.h"
#include "HeGui/HSpecSampleWidget.h"
#include "HeGui/HSpecEnergyWidget.h"
#include "HeGui/HSpecFittingChartView.h"
#include "HeGui/HSpecFittingLinearWidget.h"
#include "HeGui/HSpecPelsWaveWidget.h"
#include "HeGui/HSpecSettingDialog.h"
#include <QDebug>

HTestWidgetSpecPrivate::HTestWidgetSpecPrivate()
{
    specCalibrate = HAppContext::getContextPointer<IConfigManage>("IConfigManage")->specCalibrate("1");
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HTestWidgetSpec::HTestWidgetSpec(QWidget *parent) :
    HAbstractTestWidget(*new HTestWidgetSpecPrivate, parent),
    ui(new Ui::HTestWidgetSpec)
{
    ui->setupUi(this);
    init();
    refreshCcdView(0);
}

HTestWidgetSpec::~HTestWidgetSpec()
{
    delete ui;
}

QString HTestWidgetSpec::typeName()
{
    return "HTestWidgetSpec";
}

void HTestWidgetSpec::on_pushButton_1_clicked()
{
    Q_D(HTestWidgetSpec);
    HSpecSettingDialog dlg(static_cast<HSpecSetting *>(d->specCalibrate->item("HSpecSetting")), this);
    if (dlg.exec())
        d->model->syncTestData(ConfigContainType::CCT_Spec);
}

void HTestWidgetSpec::on_pushButton_2_clicked()
{
    Q_D(HTestWidgetSpec);
    d->pelsWaveWidget->saveData();
    d->sampleWidget->refreshLabelRight();
}

void HTestWidgetSpec::on_pushButton_3_clicked()
{
    Q_D(HTestWidgetSpec);
    d->testSetWidget->setTestState(false);
    d->fittingWidget->setTest(true);
}

void HTestWidgetSpec::on_pushButton_4_clicked()
{
    Q_D(HTestWidgetSpec);
    static_cast<HSpecStdCurve *>(d->specCalibrate->item("HSpecStdCurve"))->setCurve(d->testSpec->sample(1));
}

void HTestWidgetSpec::on_pushButton_5_clicked()
{
    Q_D(HTestWidgetSpec);
    d->fittingTimes = 0;
    d->fittingWidget->restoreDefault();
    d->ccdView->clearSeries();
}

bool HTestWidgetSpec::setTest(bool b)
{
    Q_D(HTestWidgetSpec);
    return d->testSetWidget->setTestState(b);
}

void HTestWidgetSpec::handleAction(HActionType action)
{
    Q_D(HTestWidgetSpec);
    if (action == ACT_RESET_SPECTRUM)
        return d->energyWidget->initCoordinate();
    if (action == ACT_GET_SPECTRUM)
        refreshSpecWidget();
    d->fittingWidget->handleAction(action);
    d->testSetWidget->handleAction(action);
}

void HTestWidgetSpec::handleTestStateChanged(bool b)
{
    Q_D(HTestWidgetSpec);
    d->sampleWidget->setEnablePeak(!b);
}

void HTestWidgetSpec::handleTestModeChanged(int value)
{
    Q_D(HTestWidgetSpec);
    if (value == 1)
    {
        d->testSpec->resetStdCurve();
        refreshSpecWidget();
    }
}

void HTestWidgetSpec::handleTestFitStateChanged(bool b)
{
    Q_D(HTestWidgetSpec);
    d->testSetWidget->setTestMode(b ? 2 : 0);
    d->testSetWidget->setTestState(b);
    ui->pushButton_1->setEnabled(!b);
    ui->pushButton_2->setEnabled(!b);
    ui->pushButton_3->setEnabled(!b);
    ui->pushButton_4->setEnabled(!b);
    ui->pushButton_5->setEnabled(!b);
    ui->tabWidget_1->setCurrentIndex(b ? 0 : 1);
    ui->tabWidget_2->setTabEnabled(1, !b);
}

void HTestWidgetSpec::refreshCcdView(int i)
{
    Q_D(HTestWidgetSpec);
    d->ccdView->addSeries(i, d->fittingWidget->fittingPoints().toList());
}

void HTestWidgetSpec::refreshSpecWidget()
{
    Q_D(HTestWidgetSpec);
    d->sampleWidget->refreshWidget();
    d->energyWidget->refreshWidget();
    d->detailWidget->refreshWidget();
}

void HTestWidgetSpec::init()
{
    Q_D(HTestWidgetSpec);
    d->sampleWidget = new HSpecSampleWidget;
    d->ccdView = new HSpecFittingChartView;
    d->energyWidget = new HSpecEnergyWidget;
    d->pelsWaveWidget = new HSpecPelsWaveWidget(static_cast<HSpecPelsWave *>(d->specCalibrate->item("HSpecPelsWave")));
    d->fittingWidget = new HSpecFittingLinearWidget(static_cast<HSpecFitting *>(d->specCalibrate->item("HSpecFitting")));
    d->testSetWidget = new HTestSetWidgetSpec;
    d->detailWidget = new HDetailWidgetSpec;
    ui->tabWidget_1->addTab(d->sampleWidget, d->sampleWidget->windowTitle());
    ui->tabWidget_1->addTab(d->ccdView, d->ccdView->windowTitle());
    ui->tabWidget_1->addTab(d->energyWidget, d->energyWidget->windowTitle());
    ui->tabWidget_2->addTab(d->pelsWaveWidget, d->pelsWaveWidget->windowTitle());
    ui->tabWidget_2->addTab(d->fittingWidget, d->fittingWidget->windowTitle());
    ui->tabWidget_2->addTab(d->detailWidget, d->detailWidget->windowTitle());
    ui->splitter_2->addWidget(d->testSetWidget);
    ui->splitter_2->setStretchFactor(0,1);
    ui->splitter_1->setStretchFactor(0,1);
    connect(d->testSetWidget, &ITestSetWidget::testStateChanged, this, &HTestWidgetSpec::handleTestStateChanged);
    connect(d->testSetWidget, &ITestSetWidget::testModeChanged, this, &HTestWidgetSpec::handleTestModeChanged);
    connect(d->fittingWidget, &HSpecFittingWidget::testStateChanged, this, &HTestWidgetSpec::handleTestFitStateChanged);
    connect(d->fittingWidget, &HSpecFittingWidget::fittingFinished, this, [&]{ refreshCcdView(d->fittingTimes++); });
}
