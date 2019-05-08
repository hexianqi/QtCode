#include "HSpecCalibrateSetWidget_p.h"
#include "ui_HSpecCalibrateSetWidget.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include "HeData/ITestSpec.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecCalibrateSetWidgetPrivate::HSpecCalibrateSetWidgetPrivate()
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HSpecCalibrateSetWidget::HSpecCalibrateSetWidget(QWidget *parent) :
    HAbstractTestSetWidget(*new HSpecCalibrateSetWidgetPrivate, parent),
    ui(new Ui::HSpecCalibrateSetWidget)
{
    ui->setupUi(this);
    init();
}

HSpecCalibrateSetWidget::~HSpecCalibrateSetWidget()
{
    qDebug() << __func__;
    delete ui;
}

void HSpecCalibrateSetWidget::initialize(QVariantMap /*param*/)
{

}

QString HSpecCalibrateSetWidget::typeName()
{
    return "HSpecCalibrateSetWidget";
}

void HSpecCalibrateSetWidget::handleAction(HActionType action)
{
    Q_D(HSpecCalibrateSetWidget);
    switch(action)
    {
    case ACT_SET_INTEGRAL_TIME:
        ui->doubleSpinBox_01->setValue(d->testData->data("[积分时间]").toDouble());
        break;
    case ACT_GET_SPECTRUM:
        if (!d->testState)
            break;
        if (d->integralTimeAuto && d->testSpec->adjustIntegralTime())
            d->model->addAction(ACT_SET_INTEGRAL_TIME);
        d->model->addAction(ACT_GET_SPECTRUM, 100);
        break;
    default:
        break;
    }
}

bool HSpecCalibrateSetWidget::setTestState(bool b)
{
    Q_D(HSpecCalibrateSetWidget);
    if (!HAbstractTestSetWidget::setTestState(b))
        return false;
    ui->checkBox_02->setChecked(b);
    if (b)
    {
        d->testSpec->clearCache();
        d->model->addAction(ACT_GET_SPECTRUM);
    }
    return true;
}

bool HSpecCalibrateSetWidget::setTestMode(int value)
{
    Q_D(HSpecCalibrateSetWidget);
    if (!HAbstractTestSetWidget::setTestMode(value))
        return false;

    if (d->testMode == 2)
        setIntegralTimeAuto(false);

    ui->doubleSpinBox_01->setEnabled(d->testMode == 0 && !d->integralTimeAuto);
    ui->checkBox_01->setEnabled(d->testMode == 0);
    ui->checkBox_02->setEnabled(d->testMode == 0);
    ui->radioButton_01->setEnabled(d->testMode != 2);
    ui->radioButton_02->setEnabled(d->testMode != 2);
    return true;
}

void HSpecCalibrateSetWidget::setIntegralTimeAuto(bool b)
{
    Q_D(HSpecCalibrateSetWidget);
    if (d->integralTimeAuto == b)
        return;
    d->integralTimeAuto = b;
    ui->checkBox_01->setChecked(b);
    ui->doubleSpinBox_01->setEnabled(!b);
}

void HSpecCalibrateSetWidget::on_doubleSpinBox_01_editingFinished()
{
    Q_D(HSpecCalibrateSetWidget);
    auto value = ui->doubleSpinBox_01->value();
    d->testSpec->setIntegralTime(value);
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
}

void HSpecCalibrateSetWidget::on_checkBox_01_clicked(bool b)
{
    setIntegralTimeAuto(b);
}

void HSpecCalibrateSetWidget::on_checkBox_02_clicked(bool b)
{
    setTestState(b);
}

void HSpecCalibrateSetWidget::on_radioButton_01_clicked()
{
    setTestMode(0);
}

void HSpecCalibrateSetWidget::on_radioButton_02_clicked()
{
    setTestState(false);
    setTestMode(1);
}

void HSpecCalibrateSetWidget::init()
{
    Q_D(HSpecCalibrateSetWidget);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_01);
    ui->doubleSpinBox_01->setValue(d->testData->data("[积分时间]").toDouble());
}

HE_GUI_END_NAMESPACE
