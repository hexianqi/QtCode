#include "HSpecCalibrateSetWidget2_p.h"
#include "ui_HSpecCalibrateSetWidget2.h"
#include "HeCore/HCoreHelper.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecCalibrateSetWidget2::HSpecCalibrateSetWidget2(QWidget *parent) :
    HAbstractTestSetWidget(*new HSpecCalibrateSetWidget2Private, parent),
    ui(new Ui::HSpecCalibrateSetWidget2)
{
    ui->setupUi(this);
    init();
}

HSpecCalibrateSetWidget2::~HSpecCalibrateSetWidget2()
{
    qDebug() << __func__;
    delete ui;
}

void HSpecCalibrateSetWidget2::initialize(QVariantMap /*param*/)
{

}

QString HSpecCalibrateSetWidget2::typeName()
{
    return "HSpecCalibrateSetWidget2";
}

void HSpecCalibrateSetWidget2::handleAction(HActionType action)
{
    Q_D(HSpecCalibrateSetWidget2);
    switch(action)
    {
    case ACT_SET_INTEGRAL_TIME:
        ui->doubleSpinBox_01->setValue(d->testData->data("[积分时间]").toDouble());
        break;
    case ACT_GET_SPECTRUM:
        if (!d->testState)
            break;
        adjustIntegralTime();
        d->model->addAction(ACT_GET_SPECTRUM, 100);
        break;
    default:
        break;
    }
}

bool HSpecCalibrateSetWidget2::setTestState(bool b)
{
    Q_D(HSpecCalibrateSetWidget2);
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

bool HSpecCalibrateSetWidget2::setTestMode(int value)
{
    Q_D(HSpecCalibrateSetWidget2);
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

void HSpecCalibrateSetWidget2::setIntegralTimeAuto(bool b)
{
    Q_D(HSpecCalibrateSetWidget2);
    if (d->integralTimeAuto == b)
        return;
    d->integralTimeAuto = b;
    ui->checkBox_01->setChecked(b);
    ui->doubleSpinBox_01->setEnabled(!b);
}

void HSpecCalibrateSetWidget2::on_doubleSpinBox_01_valueChanged(double value)
{
    Q_D(HSpecCalibrateSetWidget2);
    if (qFuzzyCompare(value, d->testData->data("[积分时间]").toDouble()))
        return;
    d->testData->setData("[积分时间]", value);
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
}

void HSpecCalibrateSetWidget2::on_checkBox_01_clicked(bool b)
{
    setIntegralTimeAuto(b);
}

void HSpecCalibrateSetWidget2::on_checkBox_02_clicked(bool b)
{
    setTestState(b);
}

void HSpecCalibrateSetWidget2::on_checkBox_03_clicked(bool b)
{
    Q_D(HSpecCalibrateSetWidget2);
    d->testData->setData("[电源模式]", b ? 1 : 0);
    d->model->addAction(ACT_SET_SOURCE_MODE);
}

void HSpecCalibrateSetWidget2::on_radioButton_01_clicked()
{
    setTestMode(0);
}

void HSpecCalibrateSetWidget2::on_radioButton_02_clicked()
{
    setTestState(false);
    HCoreHelper::msleep(100);
    setTestMode(1);
}

bool HSpecCalibrateSetWidget2::adjustIntegralTime()
{
    Q_D(HSpecCalibrateSetWidget2);
    if (!d->integralTimeAuto)
        return false;
    if (!d->testData->handleOperation("<匹配积分时间>").toBool())
        return false;
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
    return true;
}

void HSpecCalibrateSetWidget2::init()
{
    Q_D(HSpecCalibrateSetWidget2);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_01);
    ui->doubleSpinBox_01->setValue(d->testData->data("[积分时间]").toDouble());
}

HE_GUI_END_NAMESPACE
