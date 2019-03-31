#include "HTestSetWidgetSpec_p.h"
#include "ui_HTestSetWidgetSpec.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include "HeController/ITestSpec.h"
#include "HePlugin/HPluginHelper.h"

HTestSetWidgetSpecPrivate::HTestSetWidgetSpecPrivate()
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HTestSetWidgetSpec::HTestSetWidgetSpec(QWidget *parent) :
    HAbstractTestSetWidget(*new HTestSetWidgetSpecPrivate, parent),
    ui(new Ui::HTestSetWidgetSpec)
{
    ui->setupUi(this);
    init();
}

HTestSetWidgetSpec::~HTestSetWidgetSpec()
{
    delete ui;
}

QString HTestSetWidgetSpec::typeName()
{
    return "HTestSetWidgetSpec";
}

void HTestSetWidgetSpec::handleAction(HActionType action)
{
    Q_D(HTestSetWidgetSpec);
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
        d->model->addAction(ACT_GET_SPECTRUM);
        break;
    default:
        break;
    }
}

bool HTestSetWidgetSpec::setTestState(bool b)
{
    Q_D(HTestSetWidgetSpec);
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

bool HTestSetWidgetSpec::setTestMode(int value)
{
    Q_D(HTestSetWidgetSpec);
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

void HTestSetWidgetSpec::setIntegralTime(double value)
{
    Q_D(HTestSetWidgetSpec);
    d->testSpec->setIntegralTime(value);
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
}

void HTestSetWidgetSpec::setIntegralTimeAuto(bool b)
{
    Q_D(HTestSetWidgetSpec);
    if (d->integralTimeAuto == b)
        return;
    d->integralTimeAuto = b;
    ui->checkBox_01->setChecked(b);
    ui->doubleSpinBox_01->setEnabled(!b);
}

void HTestSetWidgetSpec::on_checkBox_01_clicked(bool b)
{
    setIntegralTimeAuto(b);
}

void HTestSetWidgetSpec::on_checkBox_02_clicked(bool b)
{
    setTestState(b);
}

void HTestSetWidgetSpec::on_radioButton_01_clicked()
{
    setTestMode(0);
}

void HTestSetWidgetSpec::on_radioButton_02_clicked()
{
    setTestState(false);
    setTestMode(1);
}

void HTestSetWidgetSpec::init()
{
    Q_D(HTestSetWidgetSpec);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_01);
    ui->doubleSpinBox_01->setValue(d->testData->data("[积分时间]").toDouble());
    connect(ui->doubleSpinBox_01, SIGNAL(valueChanged(double)), this, SLOT(setIntegralTime(double)));
}
