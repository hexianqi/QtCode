#include "HSpecCalibrateSetWidget_p.h"
#include "ui_HSpecCalibrateSetWidget.h"
#include "HeCore/HCoreHelper.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"

HE_BEGIN_NAMESPACE

HSpecCalibrateSetWidget::HSpecCalibrateSetWidget(QWidget *parent) :
    HAbstractTestSetWidget(*new HSpecCalibrateSetWidgetPrivate, parent),
    ui(new Ui::HSpecCalibrateSetWidget)
{
    ui->setupUi(this);
    init();
}

HSpecCalibrateSetWidget::~HSpecCalibrateSetWidget()
{
    delete ui;
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
        emit resultChanged(action, false);
        if (!d->testState)
            break;
        adjustIntegralTime();
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
        d->testData->handleOperation("<清空光谱采样缓存>");
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
        setAutoIntegralTime(false);

    ui->doubleSpinBox_01->setEnabled(d->testMode == 0 && !d->autoIntegralTime);
    ui->checkBox_01->setEnabled(d->testMode == 0);
    ui->checkBox_02->setEnabled(d->testMode == 0);
    ui->radioButton_01->setEnabled(d->testMode != 2);
    ui->radioButton_02->setEnabled(d->testMode != 2);
    return true;
}

void HSpecCalibrateSetWidget::setAutoIntegralTime(bool b)
{
    Q_D(HSpecCalibrateSetWidget);
    if (d->autoIntegralTime == b)
        return;
    d->autoIntegralTime = b;
    ui->checkBox_01->setChecked(b);
    ui->doubleSpinBox_01->setEnabled(!b);
}

void HSpecCalibrateSetWidget::on_doubleSpinBox_01_valueChanged(double value)
{
    Q_D(HSpecCalibrateSetWidget);
    if (d->testData->setData("[积分时间]", value))
        d->model->addAction(ACT_SET_INTEGRAL_TIME);
}

void HSpecCalibrateSetWidget::on_checkBox_01_clicked(bool b)
{
    setAutoIntegralTime(b);
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
    HCoreHelper::msleep(100);
    setTestMode(1);
}

bool HSpecCalibrateSetWidget::adjustIntegralTime()
{
    Q_D(HSpecCalibrateSetWidget);
    if (!d->autoIntegralTime)
        return false;
    if (!d->testData->handleOperation("<匹配积分时间>").toBool())
        return false;
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
    return true;
}

void HSpecCalibrateSetWidget::init()
{
    Q_D(HSpecCalibrateSetWidget);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_01);
    ui->doubleSpinBox_01->setValue(d->testData->data("[积分时间]").toDouble());
}

HE_END_NAMESPACE
