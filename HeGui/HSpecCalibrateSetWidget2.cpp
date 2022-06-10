#include "HSpecCalibrateSetWidget2_p.h"
#include "ui_HSpecCalibrateSetWidget2.h"
#include "HeCore/HCoreHelper.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"

HE_BEGIN_NAMESPACE

HSpecCalibrateSetWidget2::HSpecCalibrateSetWidget2(QWidget *parent) :
    HAbstractTestSetWidget(*new HSpecCalibrateSetWidget2Private, parent),
    ui(new Ui::HSpecCalibrateSetWidget2)
{
    ui->setupUi(this);
    init();
}

HSpecCalibrateSetWidget2::~HSpecCalibrateSetWidget2()
{
    delete ui;
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
        setAutoIntegralTime(false);

    ui->doubleSpinBox_01->setEnabled(d->testMode == 0 && !d->autoIntegralTime);
    ui->checkBox_01->setEnabled(d->testMode == 0);
    ui->checkBox_02->setEnabled(d->testMode == 0);
    ui->radioButton_01->setEnabled(d->testMode != 2);
    ui->radioButton_02->setEnabled(d->testMode != 2);
    return true;
}

void HSpecCalibrateSetWidget2::setAutoIntegralTime(bool b)
{
    Q_D(HSpecCalibrateSetWidget2);
    if (d->autoIntegralTime == b)
        return;
    d->autoIntegralTime = b;
    ui->checkBox_01->setChecked(b);
    ui->doubleSpinBox_01->setEnabled(!b);
}

void HSpecCalibrateSetWidget2::on_checkBox_01_clicked(bool b)
{
    setAutoIntegralTime(b);
}

void HSpecCalibrateSetWidget2::on_checkBox_02_clicked(bool b)
{
    setTestState(b);
}

void HSpecCalibrateSetWidget2::on_checkBox_03_clicked(bool b)
{
    setTestData("[电源模式]", b ? 1 : 0, ACT_SET_SOURCE_MODE);
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
    if (!d->autoIntegralTime)
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
    connect(ui->doubleSpinBox_01, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=] (double value) { setTestData("[积分时间]", value, ACT_SET_INTEGRAL_TIME); });
}

HE_END_NAMESPACE
