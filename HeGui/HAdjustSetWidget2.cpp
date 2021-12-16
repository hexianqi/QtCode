#include "HAdjustSetWidget2_p.h"
#include "ui_HAdjustSetWidget2.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"

HE_BEGIN_NAMESPACE

HAdjustSetWidget2::HAdjustSetWidget2(QWidget *parent) :
    HAbstractTestSetWidget(*new HAdjustSetWidget2Private, parent),
    ui(new Ui::HAdjustSetWidget2)
{
    ui->setupUi(this);
    init();
}

HAdjustSetWidget2::~HAdjustSetWidget2()
{
    delete ui;
}

QString HAdjustSetWidget2::typeName()
{
    return "HAdjustSetWidget2";
}

void HAdjustSetWidget2::handleAction(HActionType action)
{
    Q_D(HAdjustSetWidget2);
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

bool HAdjustSetWidget2::setTestState(bool b)
{
    Q_D(HAdjustSetWidget2);
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

void HAdjustSetWidget2::on_doubleSpinBox_01_valueChanged(double value)
{
    Q_D(HAdjustSetWidget2);
    if (qFuzzyCompare(value, d->testData->data("[积分时间]").toDouble()))
        return;
    d->testData->setData("[积分时间]", value);
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
}

void HAdjustSetWidget2::on_checkBox_01_clicked(bool b)
{
    Q_D(HAdjustSetWidget2);
    if (d->autoIntegralTime == b)
        return;
    d->autoIntegralTime = b;
    ui->checkBox_01->setChecked(b);
    ui->doubleSpinBox_01->setEnabled(!b);
}

void HAdjustSetWidget2::on_checkBox_02_clicked(bool b)
{
    setTestState(b);
}

void HAdjustSetWidget2::on_checkBox_03_clicked(bool b)
{
    Q_D(HAdjustSetWidget2);
    d->testData->setData("[电源模式]", b ? 1 : 0);
    d->model->addAction(ACT_SET_SOURCE_MODE);
}

bool HAdjustSetWidget2::adjustIntegralTime()
{
    Q_D(HAdjustSetWidget2);
    if (!d->autoIntegralTime)
        return false;
    if (!d->testData->handleOperation("<匹配积分时间>").toBool())
        return false;
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
    return true;
}

void HAdjustSetWidget2::init()
{
    Q_D(HAdjustSetWidget2);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_01);
    ui->doubleSpinBox_01->setValue(d->testData->data("[积分时间]").toDouble());
}

HE_END_NAMESPACE
