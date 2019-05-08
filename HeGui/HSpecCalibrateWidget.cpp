#include "HSpecCalibrateWidget_p.h"
#include "ui_HSpecCalibrateWidget.h"
#include "ITestSetWidget.h"
#include "HSpecDetailWidget.h"
#include "HSpecEnergyWidget.h"
#include "HSpecFittingChartView.h"
#include "HSpecFittingLinearWidget.h"
#include "HSpecPelsWaveWidget.h"
#include "HSpecSampleChartView.h"
#include "HSpecSettingDialog.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include "HeData/IConfigManage.h"
#include "HeData/ITestSpec.h"
#include "HeData/ISpecCalibrate.h"
#include "HeData/HSpecFitting.h"
#include "HeData/HSpecPelsWave.h"
#include "HeData/HSpecSetting.h"
#include "HeData/HSpecStdCurve.h"
#include "HeData/HSpecLuminous.h"
#include "HePlugin/HPluginHelper.h"
#include <QtWidgets/QInputDialog>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecCalibrateWidgetPrivate::HSpecCalibrateWidgetPrivate()
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HSpecCalibrateWidget::HSpecCalibrateWidget(QWidget *parent) :
    HAbstractTestWidget(*new HSpecCalibrateWidgetPrivate, parent),
    ui(new Ui::HSpecCalibrateWidget)
{
    ui->setupUi(this);
    init();
}

HSpecCalibrateWidget::~HSpecCalibrateWidget()
{
    qDebug() << __func__;
    delete ui;
}

void HSpecCalibrateWidget::initialize(QVariantMap /*param*/)
{

}

QString HSpecCalibrateWidget::typeName()
{
    return "HSpecCalibrateWidget";
}

void HSpecCalibrateWidget::setSpecCalibrate(ISpecCalibrate *p)
{
    Q_D(HSpecCalibrateWidget);
    d->specCalibrate = p;
    d->fittingWidget->setData(dynamic_cast<HSpecFitting *>(p->item(ISpecCalibrate::SpecFitting)));
    d->pelsWaveWidget->setData(dynamic_cast<HSpecPelsWave *>(p->item(ISpecCalibrate::SpecPelsWave)));
    refreshCcdView(0);
}

void HSpecCalibrateWidget::setTestSetWidget(ITestSetWidget *p)
{
    Q_D(HSpecCalibrateWidget);
    d->testSetWidget = p;
    ui->splitter_2->addWidget(d->testSetWidget);
    connect(d->testSetWidget, &ITestSetWidget::testStateChanged, this, &HSpecCalibrateWidget::handleTestStateChanged);
    connect(d->testSetWidget, &ITestSetWidget::testModeChanged, this, &HSpecCalibrateWidget::handleTestModeChanged);
}

bool HSpecCalibrateWidget::setTest(bool b)
{
    Q_D(HSpecCalibrateWidget);
    return d->testSetWidget->setTestState(b);
}

void HSpecCalibrateWidget::handleAction(HActionType action)
{
    Q_D(HSpecCalibrateWidget);
    if (action == ACT_RESET_SPECTRUM)
    {
        setTest(false);
        d->energyWidget->initCoordinate();
        return;
    }
    if (action == ACT_GET_SPECTRUM)
        refreshSpecWidget();
    d->fittingWidget->handleAction(action);
    d->testSetWidget->handleAction(action);
}

void HSpecCalibrateWidget::handleTestStateChanged(bool b)
{
    Q_D(HSpecCalibrateWidget);
    d->sampleView->setEnablePeak(!b);
}

void HSpecCalibrateWidget::handleTestModeChanged(int value)
{
    Q_D(HSpecCalibrateWidget);
    if (value == 1)
    {
        d->testSpec->resetStdCurve();
        refreshSpecWidget();
    }
}

void HSpecCalibrateWidget::handleTestFitStateChanged(bool b)
{
    Q_D(HSpecCalibrateWidget);
    d->testSetWidget->setTestMode(b ? 2 : 0);
    d->testSetWidget->setTestState(b);
    ui->pushButton_1->setEnabled(!b);
    ui->pushButton_2->setEnabled(!b);
    ui->pushButton_3->setEnabled(!b);
    ui->pushButton_4->setEnabled(!b);
    ui->pushButton_5->setEnabled(!b);
    ui->pushButton_6->setEnabled(!b);
    ui->tabWidget_1->setCurrentIndex(b ? 0 : 1);
}

void HSpecCalibrateWidget::on_tabWidget_1_currentChanged(int index)
{
    Q_UNUSED(index);
    refreshSpecWidget();
}

void HSpecCalibrateWidget::on_pushButton_1_clicked()
{
    Q_D(HSpecCalibrateWidget);
    HSpecSettingDialog dlg(this);
    dlg.setData(dynamic_cast<HSpecSetting *>(d->specCalibrate->item(ISpecCalibrate::SpecSetting)));
    if (dlg.exec())
        d->model->syncTestData(IConfigManage::ContainSpec);
}

void HSpecCalibrateWidget::on_pushButton_2_clicked()
{
    Q_D(HSpecCalibrateWidget);
    d->pelsWaveWidget->saveData();
    d->sampleView->refreshRight();
}

void HSpecCalibrateWidget::on_pushButton_3_clicked()
{
    Q_D(HSpecCalibrateWidget);
    d->testSetWidget->setTestState(false);
    d->fittingWidget->setTest(true);
}

void HSpecCalibrateWidget::on_pushButton_4_clicked()
{
    Q_D(HSpecCalibrateWidget);
    auto energy = d->testSpec->data("[明视觉能量]").toDouble();
    auto integral = d->testSpec->data("[积分时间]").toDouble();
    if (energy < 0.01)
        return;

    auto item = dynamic_cast<HSpecLuminous *>(d->specCalibrate->item(ISpecCalibrate::SpecLuminous));

    QInputDialog dlg(this);
    HPluginHelper::initWidget("[标准光谱光通量]", &dlg);
    dlg.setLabelText(tr("标准光通量："));
    dlg.setDoubleValue(item->data("[标准光谱光通量]").toDouble());
    if (dlg.exec())
    {
        item->setData("[标准光谱光通量]", dlg.doubleValue());
        item->setData("[光谱光通量系数]", dlg.doubleValue() * integral / energy);
    }
}

void HSpecCalibrateWidget::on_pushButton_5_clicked()
{
    Q_D(HSpecCalibrateWidget);
    dynamic_cast<HSpecStdCurve *>(d->specCalibrate->item(ISpecCalibrate::SpecStdCurve))->setCurve(d->testSpec->sample(1));
}

void HSpecCalibrateWidget::on_pushButton_6_clicked()
{
    Q_D(HSpecCalibrateWidget);
    d->fittingTimes = 0;
    d->fittingWidget->restoreDefault();
    d->ccdView->clearSeries();
}

void HSpecCalibrateWidget::refreshCcdView(int i)
{
    Q_D(HSpecCalibrateWidget);
    d->ccdView->addSeries(i, d->fittingWidget->fittingPoints());
}

void HSpecCalibrateWidget::refreshSpecWidget()
{
    Q_D(HSpecCalibrateWidget);
    int index = ui->tabWidget_1->currentIndex();
    if (index == 0)
        d->sampleView->refreshWidget();
    if (index == 2)
        d->energyWidget->refreshWidget();
    d->detailWidget->refreshWidget();
}

void HSpecCalibrateWidget::init()
{
    Q_D(HSpecCalibrateWidget);
    d->sampleView = new HSpecSampleChartView;
    d->ccdView = new HSpecFittingChartView;
    d->energyWidget = new HSpecEnergyWidget;
    d->pelsWaveWidget = new HSpecPelsWaveWidget;
    d->fittingWidget = new HSpecFittingLinearWidget;
    d->detailWidget = new HSpecDetailWidget;
    ui->tabWidget_1->addTab(d->sampleView, d->sampleView->windowTitle());
    ui->tabWidget_1->addTab(d->ccdView, d->ccdView->windowTitle());
    ui->tabWidget_1->addTab(d->energyWidget, d->energyWidget->windowTitle());
    ui->tabWidget_2->addTab(d->pelsWaveWidget, d->pelsWaveWidget->windowTitle());
    ui->tabWidget_2->addTab(d->fittingWidget, d->fittingWidget->windowTitle());
    ui->tabWidget_2->addTab(d->detailWidget, d->detailWidget->windowTitle());
    ui->splitter_2->setStretchFactor(0,1);
    ui->splitter_1->setStretchFactor(0,1);
    connect(d->fittingWidget, &HSpecFittingWidget::testStateChanged, this, &HSpecCalibrateWidget::handleTestFitStateChanged);
    connect(d->fittingWidget, &HSpecFittingWidget::fittingFinished, this, [&]{ refreshCcdView(d->fittingTimes++); });
}

HE_GUI_END_NAMESPACE
