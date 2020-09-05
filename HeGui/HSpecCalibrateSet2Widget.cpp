#include "HSpecCalibrateSet2Widget_p.h"
#include "ui_HSpecCalibrateSet2Widget.h"
#include "HeCore/HCoreHelper.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecCalibrateSet2Widget::HSpecCalibrateSet2Widget(QWidget *parent) :
    HAbstractTestSetWidget(*new HSpecCalibrateSet2WidgetPrivate, parent),
    ui(new Ui::HSpecCalibrateSet2Widget)
{
    ui->setupUi(this);
    init();
}

HSpecCalibrateSet2Widget::~HSpecCalibrateSet2Widget()
{
    qDebug() << __func__;
    delete ui;
}

void HSpecCalibrateSet2Widget::initialize(QVariantMap /*param*/)
{

}

QString HSpecCalibrateSet2Widget::typeName()
{
    return "HSpecCalibrateSet2Widget";
}

void HSpecCalibrateSet2Widget::handleAction(HActionType action)
{
    Q_D(HSpecCalibrateSet2Widget);
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

bool HSpecCalibrateSet2Widget::setTestState(bool b)
{
    Q_D(HSpecCalibrateSet2Widget);
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

bool HSpecCalibrateSet2Widget::setTestMode(int value)
{
    Q_D(HSpecCalibrateSet2Widget);
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

void HSpecCalibrateSet2Widget::setIntegralTimeAuto(bool b)
{
    Q_D(HSpecCalibrateSet2Widget);
    if (d->integralTimeAuto == b)
        return;
    d->integralTimeAuto = b;
    ui->checkBox_01->setChecked(b);
    ui->doubleSpinBox_01->setEnabled(!b);
}

void HSpecCalibrateSet2Widget::on_doubleSpinBox_01_valueChanged(double value)
{
    Q_D(HSpecCalibrateSet2Widget);
    if (qFuzzyCompare(value, d->testData->data("[积分时间]").toDouble()))
        return;
    d->testData->setData("[积分时间]", value);
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
}

void HSpecCalibrateSet2Widget::on_checkBox_01_clicked(bool b)
{
    setIntegralTimeAuto(b);
}

void HSpecCalibrateSet2Widget::on_checkBox_02_clicked(bool b)
{
    setTestState(b);
}

void HSpecCalibrateSet2Widget::on_checkBox_03_clicked(bool b)
{
    Q_D(HSpecCalibrateSet2Widget);
    d->testData->setData("[电源模式]", b ? 1 : 0);
    d->model->addAction(ACT_SET_SOURCE_MODE);
}

void HSpecCalibrateSet2Widget::on_radioButton_01_clicked()
{
    setTestMode(0);
}

void HSpecCalibrateSet2Widget::on_radioButton_02_clicked()
{
    setTestState(false);
    HCoreHelper::msleep(100);
    setTestMode(1);
}

bool HSpecCalibrateSet2Widget::adjustIntegralTime()
{
    Q_D(HSpecCalibrateSet2Widget);
    if (!d->integralTimeAuto)
        return false;
    if (!d->testData->handleOperation("<匹配积分时间>").toBool())
        return false;
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
    return true;
}

void HSpecCalibrateSet2Widget::init()
{
    Q_D(HSpecCalibrateSet2Widget);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_01);
    ui->doubleSpinBox_01->setValue(d->testData->data("[积分时间]").toDouble());
}

HE_GUI_END_NAMESPACE
