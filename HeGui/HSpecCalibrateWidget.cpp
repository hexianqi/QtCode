#include "HSpecCalibrateWidget_p.h"
#include "ui_HSpecCalibrateWidget.h"
#include "IGuiFactory.h"
#include "ITestSetWidget.h"
#include "HSpecDetailWidget.h"
#include "HSpecEnergyWidget.h"
#include "HSpecFittingChartView.h"
#include "HSpecFittingLinearWidget.h"
#include "HSpecFittingPolynomWidget.h"
#include "HSpecPelsWaveWidget.h"
#include "HSpecSampleChartView.h"
#include "HSpecSettingDialog.h"
#include "HeCore/HCoreHelper.h"
#include "HeController/IModel.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/ITestData.h"
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
    auto factory = HAppContext::getContextPointer<IGuiFactory>("IGuiFactory");
    auto type = HAppContext::getContextValue<QString>("SpecCalibrateSetWidgetType");
    if (type.isEmpty())
        type = "HSpecCalibrateSetWidget";
    sampleView = new HSpecSampleChartView;
    ccdView = new HSpecFittingChartView;
    energyWidget = new HSpecEnergyWidget;
    pelsWaveWidget = new HSpecPelsWaveWidget;
    detailWidget = new HSpecDetailWidget;
    testSetWidget = factory->createTestSetWidget(type);
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

void HSpecCalibrateWidget::setCalibrate(ISpecCalibrate *p)
{
    Q_D(HSpecCalibrateWidget);

    if (d->calibrate != nullptr)
        ui->tabWidget_2->removeTab(ui->tabWidget_2->indexOf(d->fittingWidget));

    auto f = dynamic_cast<HSpecFitting *>(p->item(Fitting));
    auto w = dynamic_cast<HSpecPelsWave *>(p->item(PelsWave));

    d->calibrate = p;
    if (f->typeName() == "HSpecFittingPolynom")
        d->fittingWidget = new HSpecFittingPolynomWidget;
    else
        d->fittingWidget = new HSpecFittingLinearWidget;
    d->fittingWidget->setData(f);
    d->pelsWaveWidget->setData(w);
    ui->tabWidget_2->addTab(d->fittingWidget, d->fittingWidget->windowTitle());
    connect(d->fittingWidget, &HSpecFittingWidget::stateChanged, this, &HSpecCalibrateWidget::handleFitStateChanged);
    connect(d->fittingWidget, &HSpecFittingWidget::fittingFinished, this, [=]{ refreshCcdView(); });
    refreshCcdView();
}

void HSpecCalibrateWidget::handleAction(HActionType action)
{
    Q_D(HSpecCalibrateWidget);
    d->fittingWidget->handleAction(action);
    HAbstractTestWidget::handleAction(action);
}

void HSpecCalibrateWidget::handleStateChanged(bool b)
{
    Q_D(HSpecCalibrateWidget);
    d->sampleView->setEnablePeak(!b);
}

void HSpecCalibrateWidget::handleModeChanged(int value)
{
    Q_D(HSpecCalibrateWidget);
    if (value == 1)
    {
        ui->tabWidget_1->setCurrentIndex(0);
        d->testData->handleOperation("<使用标准光谱曲线>");
        refreshSpecWidget();
    }
}

void HSpecCalibrateWidget::handleResultChanged()
{
    refreshSpecWidget();
}

void HSpecCalibrateWidget::handleFitStateChanged(bool b)
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
    ui->tabWidget_1->setCurrentIndex(b ? 0 : 2);
}

void HSpecCalibrateWidget::on_tabWidget_1_currentChanged(int index)
{
    Q_UNUSED(index);
    refreshSpecWidget();
}

void HSpecCalibrateWidget::on_pushButton_1_clicked()
{
    Q_D(HSpecCalibrateWidget);
    setTest(false);
    HSpecSettingDialog dlg(this);
    dlg.setData(dynamic_cast<HSpecSetting *>(d->calibrate->item(Setting)));
    if (dlg.exec())
    {
        d->testData->setData(d->calibrate->testParam());
        d->energyWidget->initCoordinate();
    }
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
    HCoreHelper::msleep(100);
    d->fittingWidget->setTestState(true);
}

void HSpecCalibrateWidget::on_pushButton_4_clicked()
{
    Q_D(HSpecCalibrateWidget);
    auto energy = d->testData->data("[明视觉光通量]").toDouble();
    auto integral = d->testData->data("[积分时间]").toDouble();
    if (energy < 0.01)
        return;

    auto item = d->calibrate->item(Luminous);
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
    d->testData->handleOperation("<设置标准光谱曲线>");
}

void HSpecCalibrateWidget::on_pushButton_6_clicked()
{
    Q_D(HSpecCalibrateWidget);
    d->fittingTimes = 0;
    d->fittingWidget->clearData();
    d->ccdView->clearSeries();
}

void HSpecCalibrateWidget::refreshCcdView()
{
    Q_D(HSpecCalibrateWidget);
    d->fittingTimes++;
    d->ccdView->addLineSeries(d->fittingTimes, d->fittingWidget->fittingCurve());
    d->ccdView->addScatterSeries(d->fittingTimes, d->fittingWidget->fittingPoints());
}

void HSpecCalibrateWidget::refreshSpecWidget()
{
    Q_D(HSpecCalibrateWidget);
    int index = ui->tabWidget_1->currentIndex();
    if (index == 0)
        d->sampleView->refreshWidget();
    if (index == 1)
        d->energyWidget->refreshWidget();
    d->detailWidget->refreshWidget();
}

void HSpecCalibrateWidget::init()
{
    Q_D(HSpecCalibrateWidget);
    ui->tabWidget_1->addTab(d->sampleView, d->sampleView->windowTitle());
    ui->tabWidget_1->addTab(d->energyWidget, d->energyWidget->windowTitle());
    ui->tabWidget_1->addTab(d->ccdView, d->ccdView->windowTitle());
    ui->tabWidget_2->addTab(d->pelsWaveWidget, d->pelsWaveWidget->windowTitle());
    ui->tabWidget_2->addTab(d->detailWidget, d->detailWidget->windowTitle());
    ui->splitter_1->setStretchFactor(0,1);
    ui->splitter_2->addWidget(d->testSetWidget);
    ui->splitter_2->setStretchFactor(0,1);
    connect(d->testSetWidget, &ITestSetWidget::stateChanged, this, &HSpecCalibrateWidget::handleStateChanged);
    connect(d->testSetWidget, &ITestSetWidget::modeChanged, this, &HSpecCalibrateWidget::handleModeChanged);
    connect(d->testSetWidget, &ITestSetWidget::resultChanged, this, &HSpecCalibrateWidget::handleResultChanged);
}

HE_GUI_END_NAMESPACE
